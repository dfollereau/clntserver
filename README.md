# Simple Client-server c cpp c++ language 
this repo is a simple client-server written in c/c++ to evaluate cicd doing build and testing

A server (server.c) is compiled and running in a Docker container, listening on port 8080. The container is exposing this port for outside connections.
The client (client.cpp) written in cpp (running outside container) is connecting to this Docker "C" TCP listener and sending a query (ignored) then a reply is returned.

I did this sample to evaluate various products: Openshift 3.3, Travis CI, Bamboo etc... If I have enough time, I will write a summary of my evaluations.

TravisCI: https://travis-ci.org/dfollereau/clntserver
Connected to this GitHub for a cicd

Docker registry: https://hub.docker.com/r/dfollereau/cpp-clientserver/
Artifact pushed from TravisCI
