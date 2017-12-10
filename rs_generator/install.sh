#!/bin/bash

# Make folder accessible & executable
chmod -R 777 .

# Add current folder to bashrc
echo "export PATH=\$PATH:`pwd`" >> ~/.bashrc

echo "Installation successful!"
echo "IMPORTANT: Changes will apply when logging in the next time!"
