#!/bin/bash

if [ $# -eq 1 ]
then
    kill -3 $1
else
    echo "Usage: $0 <pid>"
    exit 1
fi
