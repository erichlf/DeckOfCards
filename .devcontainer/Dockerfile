FROM ubuntu:latest

ENV DEV_USER=dev

RUN apt-get update && \
  apt-get install -y --no-install-recommends \
    build-essential \
    clang \
    clang-format \
    cmake \
    curl \
    gdb \
    git \
    g++ \
    libboost-math-dev \
    libgtest-dev \
    openssh-client \
    python3-venv \
    tar \
    unzip \
  && apt-get autoremove -y \
  && rm -rf /var/lib/apt/lists/*

WORKDIR /usr/src/googletest
RUN cmake . && \
  cmake --build . && \
  cp ./lib/libgtest*.a /usr/lib

# user 1000 already exists as ubuntu on the system so fix that
RUN apt-get update \
  && apt-get install -y --no-install-recommends sudo \
  && echo ubuntu ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/ubuntu \
  && chmod 0440 /etc/sudoers.d/ubuntu

USER ubuntu

# Set up the entrypoint
CMD ["bash"]
