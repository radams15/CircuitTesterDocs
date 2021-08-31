#!/bin/bash

podman run -it --rm -v $PWD:/docs latex bash -c "cd /docs/$1 && perl make.pl"
