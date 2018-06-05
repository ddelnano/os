# -*- mode: ruby -*-
# vi: set ft=ruby :

$script = <<-SCRIPT
echo Starting provisioning...
# Install qemu user mode and tappy to run
# our TAP unit tests
apt-get update && apt-get install -y qemu-user-static python-pip gdb
pip install tappy tap.py
SCRIPT

Vagrant.configure(2) do |config|
  config.vm.box = "ubuntu/xenial64"

  config.vm.provider "virtualbox" do |vb|
    vb.memory = "1024"
  end
  config.vm.provision "shell", inline: $script
end
