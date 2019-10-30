#!/bin/bash
echo -n -e $(tr -d '[:space:]' | sed 's/../\\x&/g')
