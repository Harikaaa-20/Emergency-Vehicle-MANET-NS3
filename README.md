# 🚑 Emergency Vehicle Priority System (NS-3 MANET)

## 📌 Overview
This project simulates an Emergency Vehicle Communication System using a Mobile Ad Hoc Network (MANET) in NS-3.  
Emergency traffic is prioritized using higher transmission parameters, enabling faster communication compared to normal traffic.

---

## ⚙️ Simulation Setup

| Parameter        | Value           |
|-----------------|----------------|
| Nodes           | 10             |
| Routing Protocol| AODV           |
| Network Type    | MANET          |
| Communication   | UDP            |
| WiFi Standard   | 802.11b        |
| Mobility Model  | Random Waypoint|

---

## 🚦 Traffic Configuration

| Type         | Data Rate | Packet Size |
|--------------|----------|-------------|
| 🚑 Emergency | 5 Mbps   | 1024 bytes  |
| 🚗 Normal    | 1 Mbps   | 512 bytes   |

---

## 📊 Results

| Metric             | Emergency | Normal |
|--------------------|----------|--------|
| Packets Sent       | 8544     | 3417   |
| Packets Received   | 8430     | 3382   |
| Packet Loss        | 114      | 35     |
| Delivery Ratio (%) | 98.66    | 98.97  |

---

## 📈 Performance Graphs
- Packets Sent Comparison  
- Packets Received Comparison  
- Packet Loss Comparison  
- Packet Delivery Ratio  

---

## ▶️ How to Run Simulation

```bash
cd ~/ns-3-dev

# Build
./ns3 configure --enable-examples
./ns3 build

# Run simulation
./ns3 run scratch/emergency_anim_final_v2
```

---

## 🎥 Visualization (NetAnim)

The simulation automatically generates:
```
results/animation.xml
```

To visualize:

```bash
cd ~/netanim/build
./NetAnim
```

Then open:
```
results/animation.xml
```

---

## 🔗 Simulation Flow

```
NS-3 Simulation
      ↓
Generates animation.xml + results.xml
      ↓
NetAnim Visualization + Graph Analysis
```

---

## 📁 Project Structure

```
src/
 └── emergency_anim_final_v2.cc

results/
 ├── results.xml
 └── animation.xml

graphs/
 ├── graphs.py
 ├── packet_loss.png
 ├── packets_received.png
 ├── packets_sent.png
 └── pdr.png
```

---

## 🎯 Key Points
- Emergency traffic achieves higher throughput  
- Packet delivery ratio remains ~99%  
- AODV ensures reliable routing in MANET  
- Simulation and visualization are integrated via animation.xml  
