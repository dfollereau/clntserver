FROM gcc:4.9
MAINTAINER Denis Follereau <dfollereau@amadeus.com>
COPY . /usr/src/myapp
WORKDIR /usr/src/myapp
RUN gcc -o myapp server.c
EXPOSE 8080
ENV PATH /usr/src/myapp:$PATH
CMD ["./myapp"]
