struct prints {
    prints() = default;
    prints(const prints&) {
        std::cout << "const &" << std::endl;
    }
    prints(prints&&) {
        std::cout << "&&" << std::endl;
    }
    prints& operator=(const prints&) {
        std::cout << "operator=(const &)" << std::endl;
        return *this;
    }
    prints& operator=(prints&&) {
        std::cout << "operator=(&&)" << std::endl;
        return *this;
    }
};
