FROM gcc:4.9
COPY . /usr/src/myapp
WORKDIR /usr/src/myapp
RUN gcc -o myapp main.c
EXPOSE 8080
ENV PATH /usr/src/myapp:$PATH
CMD ["./myapp"]
