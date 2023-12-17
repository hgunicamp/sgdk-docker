FROM amd64/ubuntu:20.04

# Installing essential environment tools.
RUN \
  apt update  \
  && DEBIAN_FRONTEND=noninteractive apt install -y \
  software-properties-common \
  build-essential \
  cmake \
  cmake-extras \
  extra-cmake-modules \
  gpg \
  git-all \
  curl \
  wget \
  exuberant-ctags \
  python3 \
  libkf5config-dev \
  libkf5auth-dev \
  libkf5package-dev \
  libkf5declarative-dev \
  libkf5coreaddons-dev \
  libkf5kcmutils-dev \
  libkf5i18n-dev \
  libqt5core5a \
  libqt5widgets5 \
  libqt5gui5 \
  libqt5qml5 \
  qt5-qmake \
  qtbase5-dev \
  gettext \
  gdb \
  blastem \
  && rm -rf /var/lib/apt/lists/*

# Installing KDbg.
RUN cd /tmp && \
  git clone -b maint https://github.com/j6t/kdbg.git && \
  cd kdbg && \
  cmake . && \
  make && \
  make install && \
  cd /tmp && \
  rm -rf kdbg
