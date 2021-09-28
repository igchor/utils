dnf config-manager --add-repo https://download.docker.com/linux/fedora/docker-ce.repo
dnf makecache
dnf install -y docker-ce git

echo "
https_proxy="http://proxy-chain.intel.com:912"
http_proxy="http://proxy-chain.intel.com:912" " >> /etc/environment

systemctl start docker

mkdir /etc/systemd/system/docker.service.d

echo "[Service]
Environment="HTTP_PROXY=http://proxy-chain.intel.com:912"
Environment="HTTPS_PROXY=http://proxy-chain.intel.com:912" " >> /etc/systemd/system/docker.service.d/http-proxy.conf

systemctl daemon-reload
systemctl restart docker
