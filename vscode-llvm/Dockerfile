FROM ghcr.io/intel/llvm/ubuntu2204_intel_drivers

RUN apt-get update && apt-get install -y \
	gpg-agent wget \
	openssh-server \
	gdb \
	gdbserver \
	pkg-config \
	libtbb2-dev
	
RUN wget -qO - https://repositories.intel.com/graphics/intel-graphics.key | gpg --dearmor --output /usr/share/keyrings/intel-graphics.gpg
RUN echo 'deb [arch=amd64 signed-by=/usr/share/keyrings/intel-graphics.gpg] https://repositories.intel.com/graphics/ubuntu focal-devel main' | \
  tee  /etc/apt/sources.list.d/intel.gpu.focal.list

RUN apt-get update && apt-get install -y \
  intel-opencl-icd \
  intel-level-zero-gpu level-zero-dev

RUN mkdir -p /var/run/sshd
RUN echo 'root:root' | chpasswd \
    && sed -i 's/#PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config \
    && sed 's@session\s*required\s*pam_loginuid.so@session optional pam_loginuid.so@g' -i /etc/pam.d/sshd

CMD ["/usr/sbin/sshd", "-D"]

EXPOSE 22

