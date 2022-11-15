FROM ghcr.io/intel/llvm/ubuntu2204_intel_drivers

RUN apt-get update && apt-get install -y openssh-server gdb gdbserver

RUN mkdir -p /var/run/sshd
RUN echo 'root:root' | chpasswd \
    && sed -i 's/#PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config \
    && sed 's@session\s*required\s*pam_loginuid.so@session optional pam_loginuid.so@g' -i /etc/pam.d/sshd

CMD ["/usr/sbin/sshd", "-D"]

EXPOSE 22
