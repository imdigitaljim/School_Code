#!/bin/bash

sysctl -w kernel.randomize_va_space=0
sysctl -w kernel.exec-shield=0

