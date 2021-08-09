#!/bin/bash

podman run -it --rm -v $PWD:/docs latex bash -c "cd /docs && perl make.pl"
