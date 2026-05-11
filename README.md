# 🏎️ Car Race — 3D Hovering Car Race Game

A 3D hovering car race game built with the **TL-Engine framework** in **C++**, featuring physics-based movement, AI opponents, particle effects, and a real-time HUD.

---

## 📖 Project Overview

The player controls a hovering car racing against an AI-controlled NPC across a circuit track. The game includes a multi-lap structure, obstacle hazards, a boost system, and immersive camera modes.

---

## ✨ Key Features

- **3-lap race** against an AI opponent with real-time progress tracking
- **Boost system** with overheat and cooldown mechanics
- **Flare bomb hazards** that deal damage and blast the player back
- **Particle effects** — fire burst on flare hit, smoke trail when health is low
- **Chase and first-person camera** modes
- **Real-time HUD** showing lap, checkpoint, speed, health, boost status, and race position
- **Countdown timer** before race start, plus Game Over / Race Complete banners

---

## 🎮 Game States

| State | Description |
|---|---|
| `kWaitingToStart` | Idle screen; waits for Space key to begin countdown |
| `kCounting` | 3-second countdown before race starts |
| `kRacing` | Core gameplay loop — physics, collisions, AI, checkpoints |
| `kRaceComplete` | Freeze cars, display winner banner |
| `kGameOver` | Triggered when player health reaches 0 |

---

## ⚙️ Player Physics & Movement

### Force-Based Motion

The player car uses a simple force integration model. Forward/backward thrust is applied each frame, opposed by a drag force proportional to velocity — producing natural acceleration and deceleration.

```
Velocity += (thrustForce + dragForce) * deltaTime
```

### Boost System

Holding **Space** activates boost, increasing thrust by 40% and raising the speed cap to 60 units. Boost is limited to **3 seconds** before overheating, with a **10-second cooldown**. Boost is automatically disabled when health drops below 50.

### Physics Parameters

| Parameter | Value |
|---|---|
| Thrust (Forward) | 38 units/s² |
| Thrust (Backward) | 19 units/s² |
| Boost Multiplier | 1.40× |
| Max Speed (Normal) | 42 units/s |
| Max Speed (Boost) | 60 units/s |
| Boost Duration | 3 seconds |
| Overheat Cooldown | 10 seconds |
| Drag Coefficient | 1.80 |

---

## 💥 Collision Detection

| Object | Method | Radius / Extent |
|---|---|---|
| Other cars / tanks / flares | Sphere–sphere | Car: 1.5u, Tank: 2.5u, Flare: 2.0u |
| Walls | Axis-Aligned Bounding Box | Half-extent: 3.0u |
| Checkpoint posts | Sphere–sphere | Half-extent: 3.0u |
| Checkpoint crossing | Point-in-rectangle | Half-width: 7u, Half-depth: 11u |

---

## 🤖 AI / NPC Behaviour

The NPC follows a pre-defined list of waypoints loaded from `waypoints.txt`. Each frame, the NPC steers toward its current target waypoint and advances to the next when it gets close enough.

---

## 🌟 Particle Systems

### Flare Explosion
When a flare hits the player, fire-textured quad particles are emitted per burst. Each particle receives a random horizontal velocity and an upward launch speed, then falls under simulated gravity until reaching ground level.

### Smoke Trail
When health falls below 50, smoke puffs are emitted from the rear of the car. Each puff is a quad attached to the car model.

---

## 📷 Camera System

### Chase Camera
Orbits behind the car. The player can adjust the offset with **arrow keys** and rotate it with the **mouse**.

### First-Person Camera
Locked to a position directly behind the car's cockpit, looking in the car's heading direction.

---

## 📂 Data-Driven Scene & Waypoints

The track is not hard-coded — two external text files define the race environment:

- **`scene.txt`** — defines the track layout and environment objects
- **`waypoints.txt`** — defines the NPC's ordered path coordinates

---

## 🖥️ HUD Layout

| Position | Display |
|---|---|
| Top-left | Current lap and checkpoint number |
| Top-centre | Race position and elapsed time |
| Top-right | Speed |
| Bottom-left | Health bar and boost warning |
| Bottom-right | Boost state |
| Bottom-centre | Status messages |
| Centre screen | Winner or Game Over banner |

---

## 🔧 Code Design & Maintainability

All numeric literals are extracted into named constants grouped by category. Tuning any aspect of the game requires changing a single value at the top of the file, with no risk of missing a duplicate literal elsewhere.

---

## 🛠️ Built With

- **Language:** C++
- **Framework:** TL-Engine
- **Module:** CO1301 — Games Concepts

---

## 👤 Author

**Moksha** — University of Central Lancashire  
Module: Games Concepts (CO1301) | Year: 2025–26
