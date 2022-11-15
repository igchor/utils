export https_proxy=http://proxy-chain.intel.com:912
export http_proxy=http://proxy-chain.intel.com:912

export DPCPP_HOME=/workspace
export PATH=$DPCPP_HOME/llvm/build/bin:$PATH
export LD_LIBRARY_PATH=$DPCPP_HOME/llvm/build/lib:$LD_LIBRARY_PATH

clang++ -fsycl -g -ggdb $DPCPP_HOME/llvm/app.cpp -o $DPCPP_HOME/llvm/app.o
