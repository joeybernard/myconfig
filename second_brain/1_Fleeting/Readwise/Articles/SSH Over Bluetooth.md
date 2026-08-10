---
created: 2026-01-12T10:26
updated: 2026-01-16T08:35
---
# SSH Over Bluetooth

![rw-book-cover](https://readwise-assets.s3.amazonaws.com/static/images/article3.5c705a01b476.png)

## Metadata
- Author: [[raspberrypi.com]]
- Full Title: SSH Over Bluetooth
- Category: #articles
- Summary: The author explains how to set up SSH access over Bluetooth PAN on Raspberry Pi devices using standard services and tools. They provide step-by-step instructions for configuring the server and client, including pairing and network setup. The author seeks advice on improving security beyond the PIN code and ensuring a proper configuration.
- URL: https://forums.raspberrypi.com/viewtopic.php?t=318323

## Highlights
- [NetDev] Name=pan0 Kind=bridge /etc/systemd/network/pan0.network [Match] Name=pan0 [Network] Address=192.168.5.1/24 DHCPServer=yes /etc/systemd/system/bt-agent.service [Unit] Description=Bluetooth Auth Agent [Service] ExecStart=/usr/bin/bt-agent -c NoInputNoOutput Type=simple [Install] WantedBy=multi-user.target /etc/systemd/system/bt-network.service [Unit] Description=Bluetooth NEP PAN After=pan0.network [Service] ExecStart=/usr/bin/bt-network -s nap pan0 Type=simple [Install] WantedBy=multi-user.target ([View Highlight](https://read.readwise.io/read/01k1hbexcfpzshb6yzkp19383g))
