#!/usr/local/bin/python3

import json
import sys
from subprocess import *

filename = 'input/simpleScene.json'
with open(filename) as f:
    data = json.load(f)

print('length is:',len(json.dumps(data).encode()))
print(json.dumps(data).encode())


