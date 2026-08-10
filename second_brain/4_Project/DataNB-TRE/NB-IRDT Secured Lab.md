---
created: 2025-01-10T13:37
updated: 2025-07-23T20:26
tags:
  - NB-IRDT
  - Projects/SRE2-0
  - Projects/DataTrust
---
# Hardware/Software
- the servers use Windows Server 2016, The EOL is Jan. 12, 2027
- the network uses the IP address space 10.0.0.1/24
- After speaking with Ying, we will change the internal network to 10.203.0.0/24, in order to avoid any future issues with the UNB network.


# Log
## 2025-04-14
- Broadcom finally released our licenses. They have been applied vSphere and vCenter. So, we no longer need a temporary connection to get these licenses.
## 2025-03-05
- Verified that we have a spare fibre pair coming into the lab, with a transceiver attached. Still need to have ITS test the fibre and do a trace of where it comes out.
- Verified the switch - [Cisco 9200L 48 port](Cisco%209200L%2048%20port.md)
- Verified the new firewall - [FortiGate 90G](FortiGate%2090G.md)
- Also have a regular LAN drop
- The terminals are [Dell Wyse 5070 terminals](Dell%20Wyse%205070%20terminals.md)

## Earlier note
From an email from Tausif, we have the following

Hi Joey,

We have 2 Esx host, each having 382GB RAM, 40 core CPU  and 17 TB of HDD.

VMs have dedicated memory and vCPU cores

Regular VM have 16GB of RAM, 4vCPU and 520GB of HDD.

High Computing VM have 64GB of RAM, 8vCPU and 520GB HDD.