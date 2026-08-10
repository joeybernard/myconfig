---
publish: "true"
----

I have struggled for quite some time, trying to have a portable development environment that I can use from anywhere. The real issue is that I move from one computer to another in my travels from home, to work, to loads of other locations. Depending on my carrying capacity at any point in time, I will pick different machines to bring with me, based on their weight. But, it might be a Linux netbook, or a Windows laptop, or a Chromebook. So I can’t depend on having a consistent OS if I wanted to have tools on a USB drive.

Some folks may point to a remote droplet to act as my development environment. And, in many cases, this would work fairly well. But, again, because I travel around so much, I don’t always have a reliable path out to the Internet. Or, I may not want certain things to be out on public networks.

I had started looking at trying to build some kind of universal filesystem and toolset that I could use across multiple OSes. That was a nightmare. There just isn’t a way to have a toolset that operates in the same way across these items. Next, I thought about carrying around some kind of virtual machine image that I could spin up wherever I happened to be. The biggest issue with this idea is that I would need to have the hosting software installed on any machine that I am currently using. If I was installing something that heavy, I might as well just install my entire toolset instead.

The next idea I had was to have some kind of small computing environment to carry around with me. I looked at maybe having a Raspberry Pi in a hard case, with a battery. Or maybe some other micro PC device. That was when I finally listened to the little voice in the back of my mind that was trying to tell me that I already had the perfect device already  —  my phone. It is actually embarassing that it took me so long to stop struggling and just think about what I already had available to me. My phone provided for all of my requirements. It has plenty of storage, plenty of battery life, loads of ways to connect, and the ability to have a consistent Linux work environment.

The first step I took was to install termux on my phone. This used to be available under the Google Play Store, but now it can be found through F-Droid. For how I use it as a development environment, this is all you need to install. If you want to use it for other tasks on your phone, there are several other packages available that will allow for this. You can also use the tool proot-distro to install and use a complete Linux distribution under termux.

Once you have termux installed, you will want to install an SSH server, so that you can log into your dev box remotely. There is a termux specific package management tool, called pkg, that you can use. You are able to also use apt, if you are coming from a Debian-based distribution. For myself, I used
```bash
apt install dropbear
```
This is the package that provides both an SSH server and an SSH client. Starting the server is as simple as
```bash
sshd
```

This works fine out of the box. If you have specific constraints, you can dig into the details of the sshd configuration. Unless you want to work with SSH keys, you will also want to set a password for this account. You can do this with the command
```bash
passwd
```
You can then connect with
```bash
ssh xxx.xxx.xxx.xxx -p 8022
```

Normally, you would need to include a username. Dropbear is not that picky, straight out of the box. In my use case, I am not overly worried about nasty people getting into my phone. If you are, you will want to dig into the details a bit more.

Once you are logged in, you will have access to most of the tools that you would expect to have under Linux. There are a few items that are missing, but with the proot-distro tool, you can install a full distribution, like Debian. This should give you everything that you could possibly need.