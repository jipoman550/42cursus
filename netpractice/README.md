*This project has been created as part of the 42 curriculum by sisung.*

## **Description**

NetPractice is a project focused on the fundamentals of computer networking. The goal is to solve 10 levels of simulated network configurations to make each network functional. Through this exercise, I learned how to configure TCP/IP addresses, understand subnet masks, and manage data routing through default gateways, routers, and switches.

## **Instructions**

### **How to Run**

1. Download and extract the project files.


2. Run the `run.sh` script in your terminal to launch the local web server and open the interface in your browser.


3. Alternatively, you can run `python3 -m http.server 49242` and navigate to `http://localhost:49242`.


4. Enter your login (`sisung`) in the interface to access your personal configuration.



### **Exporting and Submission**

* To save your progress, use the **[Get my config]** button to export a configuration file for each level.


* You must submit exactly **10 exported configuration files** (one per level).


* All 10 files must be placed at the **root of your Git repository**.



## **Resources**

### **Networking Concepts Studied**

This project covered several essential networking concepts:

#### **1. The OSI 7-Layer Model**

* **Layer 1 (Physical)**: Handles physical connections via cables, hubs, and electrical signals.
* **Layer 2 (Data Link)**: Operates using **MAC Addresses** and **Switches** to deliver data within the same local area network (LAN).
* **Layer 3 (Network)**: The domain of **Routers** and **IP Addresses**. It manages logical addressing and determines the best path for data between different networks.
* **Layer 4 (Transport)**: Ensures reliable data transfer using **TCP** (Sequence Numbers, ACKs) or fast, best-effort delivery via **UDP**. It utilizes **Port numbers** to direct traffic to specific applications (e.g., IP is the "Apartment Address," while Port is the "Room Number").
* **Layer 5 (Session)**: Manages, maintains, and terminates communication sessions between devices.
* **Layer 6 (Presentation)**: Defines data formats, including encryption (SSL/TLS) and compression (JPEG, ZIP).
* **Layer 7 (Application)**: The interface for end-user services such as **HTTP** (Web), **SMTP** (Email), and **IRC** (Chat services).

#### **2. IP Addressing & Subnetting Logic**

* **IP Address**: A unique logical address assigned to each device on a network to identify it and enable communication.
* **Subnet Masks**: Define the boundaries of a network and determine the range of available host addresses (e.g., /24, /25, /30) .
* **Default Gateway**: The designated exit point (Router interface) for packets destined for a network outside the local subnet .
* **Communication Conditions**: For two hosts to communicate, they must either recognize each other as being in the same "neighborhood" (Subnet) or both must have a valid path to a **Default Gateway**.
* **Network ID Extraction**: Calculated using a bitwise AND operation between the IP and the Mask ($IP \ \& \ Mask = Network \ ID$).


#### **3. Hardware Identification & Resolution**

* **Router**: A Layer 3 device that connects multiple distinct networks and determines the best path for packets using IP addresses and routing tables.
* **Switch**: A Layer 2 device that connects multiple devices within the same network segment and manages local traffic using MAC addresses.
* **MAC (Media Access Control) Address**: A unique, permanent hardware identifier embedded in a Network Interface Card (NIC).
* **ARP (Address Resolution Protocol)**: A mechanism used to discover the MAC address of a device when only its IP address is known. This is essential for delivering packets over a physical link.
* **Packet**: The basic unit of data transmitted over a network, containing both the payload and header information (source/destination addresses).

#### **4. TCP/IP Suite vs. Individual Protocols**

* **TCP/IP Suite**: A standard set of communication protocols used to interconnect network devices on the internet. It acts as a "set menu" that includes various protocols like TCP, UDP, and IP.
* **IP (Internet Protocol)**: A single protocol within the suite responsible for **addressing and routing** packets to the correct destination (The "Delivery System").
* **TCP (Transmission Control Protocol)**: A protocol within the suite that ensures data is delivered **reliably, in the correct order, and without errors** (The "Reliability System").

#### **5. Physical Ports vs. Logical Ports (Layer 4)**

* **Hardware Ports (Physical)**: These are the actual physical connectors (e.g., RJ45 jacks) on a **Router or Switch** used to plug in Ethernet cables. They define the physical topology of the network at Layer 1 and Layer 2.
* **Software Ports (Logical/L4)**: These are 16-bit numbers (ranging from 0 to 65535) used at the **Transport Layer (Layer 4)** to identify specific applications or services on a device.
* **The Distinction**: While a Hardware Port facilitates the **physical path** for data, a Logical Port acts as a **"Room Number"** inside a building (IP address), ensuring the data reaches the correct software (e.g., Port 80 for HTTP, Port 6667 for IRC).

### **AI Usage Disclosure**

AI was utilized as a collaborative tutor during this project to strengthen my understanding of complex scenarios:

* **Troubleshooting**: AI helped analyze error logs such as "multiple interface match" (Level 4) and "private subnets not routed" (Level 9), explaining the underlying logic of subnet overlaps.
* **Mathematical Explanation**: AI assisted in calculating CIDR ranges and bitwise AND operations for non-standard masks like /18 or /26.
* **Logical Validation**: After solving levels, I used AI to verify why certain routing paths (Static Routes) were necessary for return traffic (Reverse Way).
* **README Generation**: AI assisted in formatting this documentation to ensure all 42 curriculum requirements were met.
