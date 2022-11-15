WORKDIR=/root/tmp

rsync -r --exclude build $(pwd) root@10.91.28.42:$WORKDIR
ssh root@10.91.28.42 docker run -e http_proxy="http://proxy-chain.intel.com:912" -e https_proxy="http://proxy-chain.intel.com:912" -v $WORKDIR:/workspace -w /workspace ghcr.io/intel/llvm/ubuntu2004_intel_drivers /workspace/llvm/build.sh
sudo rsync -rl root@10.91.28.42:$WORKDIR/llvm/build .
