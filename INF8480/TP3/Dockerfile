FROM ubuntu:focal

RUN apt-get update && \
  apt-get install -y software-properties-common && \
  add-apt-repository ppa:gluster/glusterfs-6 && \
  apt-get update && \ 
  apt-get install -y glusterfs-server

EXPOSE 2222 111 245 443 24006 24007 2049 8080 6010 6011 6012 38465 38466 38468 38469 49152 49153 49154 49156 49157 49158 49159 49160 49161 49162
CMD ["/bin/bash"]