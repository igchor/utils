#include <iostream>
#include <sstream>
#include <chrono>
#include <string>
#include <thread>
#include <atomic>
#include <functional>
#include <cstring>
#include <unordered_map>

// taken from: https://stackoverflow.com/questions/1872220/is-it-possible-to-iterate-over-arguments-in-variadic-macros
// Make a FOREACH macro
#define FE_0(WHAT)
#define FE_1(WHAT, X) WHAT(X) 
#define FE_2(WHAT, X, ...) WHAT(X)FE_1(WHAT, __VA_ARGS__)
#define FE_3(WHAT, X, ...) WHAT(X)FE_2(WHAT, __VA_ARGS__)
#define FE_4(WHAT, X, ...) WHAT(X)FE_3(WHAT, __VA_ARGS__)
#define FE_5(WHAT, X, ...) WHAT(X)FE_4(WHAT, __VA_ARGS__)
#define FE_6(WHAT, X, ...) WHAT(X)FE_5(WHAT, __VA_ARGS__)
#define FE_7(WHAT, X, ...) WHAT(X)FE_6(WHAT, __VA_ARGS__)
#define FE_8(WHAT, X, ...) WHAT(X)FE_7(WHAT, __VA_ARGS__)
#define FE_9(WHAT, X, ...) WHAT(X)FE_8(WHAT, __VA_ARGS__)
#define FE_10(WHAT, X, ...) WHAT(X)FE_9(WHAT, __VA_ARGS__)

#define GET_MACRO(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,NAME,...) NAME 
#define FOR_EACH(action,...) \
  GET_MACRO(_0,__VA_ARGS__,FE_10,FE_9,FE_8,FE_7,FE_6,FE_5,FE_4,FE_3,FE_2,FE_1,FE_0)(action,__VA_ARGS__)

#define STRIGIFY(X) #X,

#define TO_STRING_LIST(...) FOR_EACH(STRIGIFY,__VA_ARGS__)

#define TRACER_EVENT(NAME, ...) \
    enum tracerEvents##NAME {invalid##NAME = 0, __VA_ARGS__}; \
    static constexpr const char* tracerToStr[] = {"invalid", TO_STRING_LIST(__VA_ARGS__)}; \
    std::ostream& operator<<(std::ostream &os, enum tracerEvents##NAME e) {os << tracerToStr[e]; return os;}

TRACER_EVENT(TRACER, ev1, ev2, ev3)

template <typename EventT>
struct tracer_event_info {
    EventT event;
    std::chrono::time_point<std::chrono::system_clock> timestamp;
    std::thread::id tid;
};

// taken from: https:://github.com/facebook/CacheLib
static inline std::string formatTime(std::chrono::time_point<std::chrono::system_clock> tp) {
  // Out format is fixed size. It needs 16 chars with terminating null. For
  // safety (if someone changes the strftime format) I made it double of it.
  char buf[32];
  size_t bufSize{sizeof buf};
  auto tt = std::chrono::system_clock::to_time_t(tp);
  struct tm tm_time;
  ::localtime_r(&tt, &tm_time);
  ::strftime(buf, bufSize, "%H:%M:%S", &tm_time);
  auto len = std::strlen(buf);
  auto micros = std::chrono::duration_cast<std::chrono::microseconds>(
      tp.time_since_epoch());
  std::snprintf(buf + len,
                bufSize - len,
                ".%06d",
                static_cast<int>(micros.count() % 1'000'000));
  return buf;
}

template <typename EventT>
struct tracer_buffer {
    static constexpr size_t BUFFER_SIZE = 128;
    tracer_event_info<EventT> events[BUFFER_SIZE];
    std::atomic<int> index = 0;

    tracer_buffer() {
        for (size_t i = 0; i < BUFFER_SIZE; i++) {
            events[i].event = (decltype(events[i].event)) 0;
        }
    }

    void addEvent(const EventT& event) {
        tracer_event_info<EventT> event_info;
        event_info.event = event;
        event_info.timestamp = std::chrono::system_clock::now();
        event_info.tid = std::this_thread::get_id();
        events[index.fetch_add(1, std::memory_order_acq_rel) % BUFFER_SIZE] = event_info;
    }

    std::string toString(
        std::function<void(std::ostream&, std::chrono::time_point<std::chrono::system_clock>)> timestampProcess = 
            [](std::ostream& out, std::chrono::time_point<std::chrono::system_clock> tp){
                out << formatTime(tp);
                },
        std::function<void(std::ostream&, std::thread::id)> tidProcess =
            [](std::ostream& out, std::thread::id id) {
                out << id;
                }) {
        int i = 0;
        std::ostringstream out;
        while (true) {
            if (i == BUFFER_SIZE || (int) events[i].event == 0) {
                break;
            }

            out << "Type: " << events[i].event << "; Timestamp: ";
            timestampProcess(out, events[i].timestamp);
            out << "; tid: ";
            tidProcess(out, events[i].tid);
            out << std::endl;

            i++;
        }
        return out.str();
    }
};

using TracerMap = std::unordered_map<std::string, tracer_buffer<tracerEventsTRACER>>;

static inline TracerMap& getTracerMap() {
    static TracerMap map;
    return map;
}

template <typename K, typename V, typename TracerMapT>
void addEventToTracerMap(TracerMapT& map, K&& k, V&& v) {
    auto it = map.find(k);
    if (it == map.end()) {
        it = map.try_emplace(std::forward<K>(k)).first;
    }
    it->second.addEvent(v);
}

template <typename K, typename TracerMapT>
std::string getEventsFromTracerMap(TracerMapT& map, K&& k) {
    auto it = map.find(std::forward<K>(k));
    if (it != map.end()) {
        return it->second.toString();
    }
    return "";
}

int main() {
    addEventToTracerMap(getTracerMap(), "key1", ev2);
    addEventToTracerMap(getTracerMap(), "key1", ev1);
    addEventToTracerMap(getTracerMap(), "key2", ev1);

    std::cout << getEventsFromTracerMap(getTracerMap(), "key2");
}
