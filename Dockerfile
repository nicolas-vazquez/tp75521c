# Base image
FROM ubuntu:14.04

# Autor: fedefarina / mantiene: fedefarina
MAINTAINER fedefarina <federicojosefarina@gmail.com>

# Copio los directorios del repositorio
COPY ./ /home

# Set Locale otherwise some applications may behave strangely when
# the encoding looks like ANSI_X3.4-1968
RUN locale-gen en_GB.UTF-8
ENV LANG=en_GB.UTF-8 \
    LANGUAGE=en_GB:en \
    LC_ALL=en_GB.UTF-8

RUN apt-get update && apt-get -y upgrade && apt-get -y install wget

RUN apt-get -y --no-install-recommends install \
  build-essential \
  clang-${LLVM_VERSION} \
  cmake \
  cmake-curses-gui \
  coreutils \
  gcc \
  g++ \
  gdb \
  git-core \
  htop \
  mercurial \
  ncdu \
  ninja-build \
  python \
  python-dev \
  python-pip \
  subversion \
  tmux \
  tree \
  unzip \
  vim

# Use install scripts
RUN cd /home/AppServer && ./install.sh -docker

# Defino el directorio para correr
WORKDIR /home/AppServer/build

# Defino el comando estándar
CMD ["bash"]
