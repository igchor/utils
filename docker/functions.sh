docker_run() {
	workspace=$1
	image=$2
	sudo docker run --network=bridge --shm-size=4G -v $workspace:/opt/workspace:Z -w /opt/workspace/ -e --env http_proxy=$http_proxy --env https_proxy=$https_proxy -it $image /bin/bash
}

docker_build() {
	image_name=$1
	image_file=$2
	sudo docker build --build-arg https_proxy=$https_proxy --build-arg http_proxy=$http_proxy -t $image_name -f $image_file .
}
