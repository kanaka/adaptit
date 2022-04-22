ARG DISTRO
FROM ${DISTRO}

# Installs the `dpkg-buildpackage` command
RUN apt-get -y update && \
    DEBIAN_FRONTEND=noninteractive apt-get -y install build-essential debhelper devscripts equivs

# Copies your code file from your action repository to the filesystem path `/` of the container
COPY build.sh /build.sh

CMD ["/build.sh"]
