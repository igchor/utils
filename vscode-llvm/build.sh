export https_proxy=http://proxy-chain.intel.com:912
export http_proxy=http://proxy-chain.intel.com:912

export DPCPP_HOME=/workspace
#python $DPCPP_HOME/llvm/buildbot/configure.py -t Debug
python $DPCPP_HOME/llvm/buildbot/compile.py -j $(nproc)
# export PATH=$DPCPP_HOME/llvm/build/bin:$PATH
# export LD_LIBRARY_PATH=$DPCPP_HOME/llvm/build/lib:$LD_LIBRARY_PATH