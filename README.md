# Prisma Engine

## Dependencies
- GLEW
- Dear ImGUI
- stb
- spdlog

## Coordinate system and rotations

The engine use a right-handed coordinate system with:
- X = right
- Y = up
- Z = forward

Rotations are applied in the following order: Y->X->Z (or Yaw->Pitch->Roll).