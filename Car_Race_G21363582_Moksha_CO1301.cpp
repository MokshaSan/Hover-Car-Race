// G21363582 | R.M.M. Sandavirage | CO1301 | Assignment2 | Car Race

#define _USE_MATH_DEFINES
#include <TL-Engine.h>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace tle;
using namespace std;

const char* kMediaFolder = "C:\\Users\\Moksha\\Desktop\\CarRace\\models";
const char* kSceneFile = "C:\\Users\\Moksha\\Desktop\\CarRace\\scene.txt";
const char* kWaypointsFile = "C:\\Users\\Moksha\\Desktop\\CarRace\\waypoints.txt";

// World
const float kMetersPerUnit = 0.25f;
const float kHoverBaseY = 5.0f;
const float kHoverAmplitude = 0.35f;
const float kHoverFrequency = 4.0f;
const float kGroundY = -1.0f;
const float kOffscreenY = -100.0f;
const float kSkyY = -750.0f;
const float kModelSpawnY = 0.0f;

// Collision radii
const float kCarRadius = 1.5f;
const float kTankRadius = 2.5f;
const float kCheckpointPostRadius = 3.0f;
const float kFlareRadius = 2.0f;
const float kWallHalfExtent = 3.0f;

// Bounce multipliers
const float kBarrierBounce = 0.40f;
const float kTankBounce = 0.30f;
const float kNpcBounce = 0.35f;
const float kCheckpointBounce = 0.25f;
const float kFlareBlastMultiplier = 1.0f;

// Player physics
const float kThrustForward = 38.0f;
const float kThrustBackward = 19.0f;
const float kBoostMultiplier = 1.40f;
const float kDrag = 1.80f;
const float kOverheatDragMult = 1.50f;
const float kMaxSpeedNormal = 42.0f;
const float kMaxSpeedBoost = 60.0f;
const float kTurnSpeed = 70.0f;
const float kLeanAmount = 10.0f;
const float kPitchAmount = 5.0f;
const float kPitchSmoothing = 6.0f;

// Boost
const float kBoostMaxTime = 3.0f;
const float kBoostCooldownTime = 10.0f;
const int   kBoostDisabledHealth = 50;
const float kBoostWarningTime = 2.0f;

// Damage
const int   kMaxHealth = 100;
const int   kMinHealth = 0;
const int   kFlareDamage = 10;
const int   kCollisionDamage = 1;
const float kDamageCooldown = 0.35f;
const float kFlareCooldown = 2.0f;

// Race
const int   kTotalLaps = 3;
const int   kNumRacers = 2;
const int   kFirstPlace = 1;
const int   kSecondPlace = 2;
const float kCountdownDuration = 3.0f;
const float kMpsToKmph = 3.6f;

// Checkpoint geometry
const float kCheckpointHalfWidth = 7.0f;
const float kCheckpointHalfDepth = 11.0f;
const float kCheckpointPostOffset = 8.5f;
const int   kCheckpointDisplayOffset = 1;

// NPC
const float kNpcSpeed = 16.0f;
const float kNpcTurnSpeed = 90.0f;
const float kNpcWaypointRadius = 4.0f;
const float kNpcWallPushbackFactor = 1.5f;

// Camera
const float kCameraMoveSpeed = 25.0f;
const float kCameraTurnSpeed = 0.08f;
const float kCameraPitchMin = -15.0f;
const float kCameraPitchMax = 30.0f;
const float kFirstPersonOffsetZ = 2.5f;
const float kFirstPersonOffsetY = 3.5f;

// Cross marker
const float kCrossLifetime = 3.0f;
const float kCrossYOffset = 0.2f;

// Model scales
const float kIsleScale = 1.4f;
const float kWallScale = 1.6f;
const float kCheckpointScale = 1.35f;
const float kTankScale = 1.15f;
const float kCarScale = 0.4f;
const float kParticleScale = 0.2f;

// Particles (flare burst)
const int   kNumParticles = 1000;
const int   kParticlesPerBurst = 50;
const float kParticleGravity = -20.0f;
const float kParticleInitUpSpeed = 20.0f;
const float kParticleRandomSpeed = 6.0f;
const float kParticleOffsetRange = 2.0f;
const int   kRandMod360 = 360;
const int   kRandMod100 = 100;
const float kRandDivisor50 = 50.0f;
const float kRandSubOne = 1.0f;
const float kRandDivisor100 = 100.0f;
const float kRandSpeedDivisor20 = 20.0f;

// Smoke particle system
const int   kNumSmokeParticles = 100;
const float kSmokeEmitInterval = 0.05f;
const float kSmokeRiseSpeed = 10.0f;
const float kSmokeSpread = 0.5f; 
const float kSmokeLifetime = 4.0f;
const float kSmokeLocalOffsetY = 0.5f;
const float kSmokeLocalOffsetZ = -2.5f;
const float kSmokeScale = 0.3f; 
const char* kSmokeTexture = "smoke1.png";

// Angle conversion
const float kRadToDeg = 180.0f / static_cast<float>(M_PI);
const float kDegToRad = static_cast<float>(M_PI) / 180.0f;
const float kHalfCircleDeg = 180.0f;
const float kFullCircleDeg = 360.0f;

// World origin / start positions
const float kOriginX = 0.0f;
const float kOriginZ = 0.0f;
const float kPlayerStartX = 3.0f;
const float kPlayerStartZ = -15.0f;
const float kNpcStartX = -3.0f;
const float kNpcStartZ = -15.0f;

// Progress / increment steps
const int kLapNumberOffset = 1;
const int kWaypointIncrement = 1;
const int kCheckpointIncrement = 1;
const int kLapIncrement = 1;

// Fonts
const char* kFontName = "Algerian";
const int   kHUDFontSize = 25;
const int   kBigFontSize = 30;
const int   kAlertFontSize = 30;
const int   kHintFontSize = 25;
const int   kBannerFontSize = 36;

// Skins / textures
const char* kNpcSkinFile = "td_interstellar.jpg";
const char* kParticleTexture = "fire1.png";

// Scene type name strings
const char* kTypeIsle = "Isle";
const char* kTypeWall = "Wall";
const char* kTypeCheckpoint = "Checkpoint";
const char* kTypeTank1 = "Tank1";
const char* kTypeTank2 = "Tank2";
const char* kTypeFlare = "Flare";

// Key bindings
const EKeyCode kKeyRestart = Key_R;
const EKeyCode kKeyCamChase = Key_1;
const EKeyCode kKeyCamFirst = Key_2;
const EKeyCode kKeyBoost = Key_Space;
const EKeyCode kKeyStart = Key_Space;
const EKeyCode kKeyThrustForward = Key_W;
const EKeyCode kKeyThrustBack = Key_S;
const EKeyCode kKeyTurnLeft = Key_A;
const EKeyCode kKeyTurnRight = Key_D;

// HUD layout positions
const int kHUDMarginX = 20;
const int kHUDMarginY = 20;
const int kHUDLineSpacing = 24;
const int kHUDPlayerPosX = 40;
const int kHUDPlayerPosY = 16;
const int kHUDTimeX = 45;
const int kHUDTimeY = 46;
const int kHUDSpeedX = 160;
const int kHUDSpeedY = 16;
const int kHUDHealthY = 80;
const int kHUDHealthWarningY = 54;
const int kHUDWarningY = 80;
const int kHUDCooldownY = 54;
const int kHUDBoostX = 200;
const int kHUDStatusY = 55;
const int kHUDStatusWidth = 100;
const int kHUDHintY = 24;
const int kHUDBannerY = 30;
const int kHUDBannerWidth = 200;
const int kHUDBannerGameOverWidth = 160;

// Camera defaults
const float kDefaultCamOffsetX = 0.0f;
const float kDefaultCamOffsetY = 8.0f;
const float kDefaultCamOffsetZ = -14.0f;
const float kDefaultCamHeading = 0.0f;
const float kDefaultCamPitch = 15.0f;

// Misc
const float kNormalSpeedMultiplier = 1.0f;
const float kRotationRightAngle = 90.0f;
const int   kTimerPrecision = 2;

//   
//  MATH TYPES
//   

struct Vector2
{
    float x = 0.0f, z = 0.0f;

    Vector2() = default;
    Vector2(float x, float z) : x(x), z(z) {}

    Vector2  operator+(const Vector2& rightHandSide) const { return { x + rightHandSide.x, z + rightHandSide.z }; }
    Vector2  operator-(const Vector2& rightHandSide) const { return { x - rightHandSide.x, z - rightHandSide.z }; }
    Vector2  operator*(float scalar)       const { return { x * scalar, z * scalar }; }
    Vector2& operator+=(const Vector2& rightHandSide) { x += rightHandSide.x; z += rightHandSide.z; return *this; }

    float LengthSquared() const { return x * x + z * z; }
    float Length()        const { return sqrtf(LengthSquared()); }

    Vector2 Normalized() const
    {
        float len = Length();
        return (len > 0.0f) ? Vector2(x / len, z / len) : Vector2(kOriginX, kOriginZ);
    }
};

struct Vector3
{
    float x = 0.0f, y = 0.0f, z = 0.0f;
    Vector3() = default;
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
};

//  ENUMS
enum class GameState { kWaitingToStart, kCounting, kRacing, kRaceComplete, kGameOver };
enum class CameraMode { kChase, kFirstPerson };

//  DATA STRUCTURES
struct CheckpointData
{
    IModel* model = nullptr;
    float   x = 0.0f;
    float   z = 0.0f;
    float   rotationY = 0.0f;
};

struct CrossMarker
{
    IModel* model = nullptr;
    float   lifeTimer = 0.0f;
};

struct SceneItem
{
    string type;
    float  x = 0.0f;
    float  z = 0.0f;
    float  rotationY = 0.0f;
};

struct FlareBomb
{
    IModel* model = nullptr;
    float   x = 0.0f;
    float   z = 0.0f;
    float   cooldownTimer = 0.0f;
};

struct Particle
{
    IModel* model = nullptr;
    Vector3  velocity;
    bool     alive = false;
};

//  SMOKE PARTICLE SYSTEM
struct SmokeParticle
{
    IModel* model = nullptr;
    float   lifeTimer = 0.0f;
    bool    alive = false;
};

//  BOOST / PLAYER / NPC STATE
struct BoostState
{
    bool  active = false;
    bool  overheated = false;
    bool  ready = true;
    float activeTimer = 0.0f;
    float cooldown = 0.0f;
};

struct PlayerState
{
    Vector2    velocity;
    float      Heading = 0.0f;
    int        health = kMaxHealth;
    float      damageCooldown = 0.0f;
    int        lap = kLapIncrement;
    int        nextCheckpoint = 0;
    float      raceTime = 0.0f;
    float      currentPitch = 0.0f;
    float      targetPitch = 0.0f;
    BoostState boost;
};

struct NpcState
{
    Vector2 velocity;
    float   Heading = 0.0f;
    int     waypointIndex = 0;
    int     lap = kLapIncrement;
    int     nextCheckpoint = 0;
    float   raceTime = 0.0f;
};

struct CameraState
{
    float offsetX = kDefaultCamOffsetX;
    float offsetY = kDefaultCamOffsetY;
    float offsetZ = kDefaultCamOffsetZ;
    float Heading = kDefaultCamHeading;
    float pitch = kDefaultCamPitch;
};

struct Scene
{
    vector<IModel*>        isles, walls, tanks;
    vector<CheckpointData> checkpoints;
    vector<CrossMarker>    crosses;
    vector<FlareBomb>      flares;
};

//  COLLISION FUNCTIONS
bool CheckCollisionSphereSphere(float x1, float z1, float radius1,
    float x2, float z2, float radius2)
{
    float dx = x1 - x2;
    float dz = z1 - z2;
    float sumR = radius1 + radius2;
    return (dx * dx + dz * dz) < (sumR * sumR);
}

bool CheckCollisionPointInCheckpointGap(float pointX, float pointZ,
    const CheckpointData& checkpoint)
{
    float localX = pointX - checkpoint.x;
    float localZ = pointZ - checkpoint.z;

    if (checkpoint.rotationY == kRotationRightAngle)
        return fabsf(localX) < kCheckpointHalfDepth && fabsf(localZ) < kCheckpointHalfWidth;

    return fabsf(localX) < kCheckpointHalfWidth && fabsf(localZ) < kCheckpointHalfDepth;
}

bool CheckCollisionCheckpointPost(float carX, float carZ,
    const CheckpointData& checkpoint)
{
    float leftX = checkpoint.x, leftZ = checkpoint.z;
    float rightX = checkpoint.x, rightZ = checkpoint.z;

    if (checkpoint.rotationY == kRotationRightAngle)
    {
        leftZ -= kCheckpointPostOffset;
        rightZ += kCheckpointPostOffset;
    }
    else
    {
        leftX -= kCheckpointPostOffset;
        rightX += kCheckpointPostOffset;
    }

    return CheckCollisionSphereSphere(carX, carZ, kCarRadius, leftX, leftZ, kCheckpointPostRadius)
        || CheckCollisionSphereSphere(carX, carZ, kCarRadius, rightX, rightZ, kCheckpointPostRadius);
}

bool CheckCollisionAxisAlignedBox(float pointX, float pointZ,
    float wallX, float wallZ,
    float halfExtent)
{
    return fabsf(pointX - wallX) < halfExtent && fabsf(pointZ - wallZ) < halfExtent;
}

//  FILE LOADING FUNCTIONS
bool LoadSceneFromFile(const string& filePath, vector<SceneItem>& outItems)
{
    ifstream file(filePath);
    if (!file) return false;

    string line;
    while (getline(file, line))
    {
        if (line.empty() || line[0] == '#') continue;
        istringstream stream(line);
        SceneItem item;
        stream >> item.type >> item.x >> item.z >> item.rotationY;
        if (!stream.fail()) outItems.push_back(item);
    }
    return true;
}

bool LoadWaypointsFromFile(const string& filePath, vector<Vector2>& outWaypoints)
{
    ifstream file(filePath);
    if (!file) return false;

    string line;
    while (getline(file, line))
    {
        if (line.empty() || line[0] == '#') continue;
        istringstream stream(line);
        Vector2 waypoint;
        stream >> waypoint.x >> waypoint.z;
        if (!stream.fail()) outWaypoints.push_back(waypoint);
    }
    return true;
}

//  FLARE PARTICLE FUNCTIONS
void EmitParticles(Particle particles[], int totalParticles,
    float centerX, float centerZ, float centerY)
{
    int emitted = 0;
    for (int i = 0; i < totalParticles && emitted < kParticlesPerBurst; ++i)
    {
        if (particles[i].alive || !particles[i].model) continue;

        float offsetX = ((rand() % kRandMod100) / kRandDivisor50 - kRandSubOne) * kParticleOffsetRange;
        float offsetZ = ((rand() % kRandMod100) / kRandDivisor50 - kRandSubOne) * kParticleOffsetRange;
        particles[i].model->SetPosition(centerX + offsetX, centerY, centerZ + offsetZ);

        float randomHeading = (rand() % kRandMod360) * kDegToRad;
        float horizontalSpeed = (rand() % kRandMod100) / kRandDivisor100 * kParticleRandomSpeed;

        particles[i].velocity = Vector3(
            sinf(randomHeading) * horizontalSpeed,
            kParticleInitUpSpeed + (rand() % kRandMod100) / kRandSpeedDivisor20,
            cosf(randomHeading) * horizontalSpeed);

        particles[i].alive = true;
        ++emitted;
    }
}

void UpdateParticles(Particle particles[], int totalParticles, float deltaTime)
{
    for (int i = 0; i < totalParticles; ++i)
    {
        Particle& particle = particles[i];
        if (!particle.alive || !particle.model) continue;

        particle.velocity.y += kParticleGravity * deltaTime;
        particle.model->Move(particle.velocity.x * deltaTime,
            particle.velocity.y * deltaTime,
            particle.velocity.z * deltaTime);

        if (particle.model->GetY() <= kGroundY)
        {
            particle.alive = false;
            particle.model->SetPosition(kOriginX, kOffscreenY, kOriginZ);
        }
    }
}

//  SMOKE PARTICLE FUNCTIONS
void InitSmokeParticles(SmokeParticle smokeParticles[], int totalSmoke,
    IMesh* quadMesh, IModel* playerCarModel)
{
    for (int i = 0; i < totalSmoke; ++i)
    {
        IModel* quad = quadMesh->CreateModel(kOriginX, kOffscreenY, kOriginZ);
        if (quad)
        {
            quad->Scale(kSmokeScale);
            quad->SetSkin(kSmokeTexture);
            quad->AttachToParent(playerCarModel); 
        }
        smokeParticles[i].model = quad;
        smokeParticles[i].lifeTimer = 0.0f;
        smokeParticles[i].alive = false;
    }
}

void EmitSmokePuff(SmokeParticle smokeParticles[], int totalSmoke)
{
    for (int i = 0; i < totalSmoke; ++i)
    {
        if (smokeParticles[i].alive || !smokeParticles[i].model) continue;

        
        float spreadX = ((rand() % kRandMod100) / kRandDivisor50 - kRandSubOne) * kSmokeSpread;
        float spreadZ = ((rand() % kRandMod100) / kRandDivisor50 - kRandSubOne) * kSmokeSpread;

        
        smokeParticles[i].model->SetPosition(spreadX,
            kSmokeLocalOffsetY,
            kSmokeLocalOffsetZ + spreadZ);

        smokeParticles[i].lifeTimer = kSmokeLifetime;
        smokeParticles[i].alive = true;
        break;
    }
}

//  drift puffs upward 
void UpdateSmokeParticles(SmokeParticle smokeParticles[], int totalSmoke, float deltaTime)
{
    for (int i = 0; i < totalSmoke; ++i)
    {
        SmokeParticle& puff = smokeParticles[i];
        if (!puff.alive || !puff.model) continue;

        
        puff.model->MoveY(kSmokeRiseSpeed * deltaTime);

        puff.lifeTimer -= deltaTime;
        if (puff.lifeTimer <= 0.0f)
        {
            
            puff.model->SetPosition(kOriginX, kOffscreenY, kOriginZ);
            puff.alive = false;
        }
    }
}

// Hide all smoke
void ResetSmokeParticles(SmokeParticle smokeParticles[], int totalSmoke)
{
    for (int i = 0; i < totalSmoke; ++i)
    {
        smokeParticles[i].alive = false;
        smokeParticles[i].lifeTimer = 0.0f;
        if (smokeParticles[i].model)
            smokeParticles[i].model->SetPosition(kOriginX, kOffscreenY, kOriginZ);
    }
}

//  CAMERA FUNCTIONS
void ResetCamera(CameraState& cameraState, CameraMode& cameraMode)
{
    cameraState = { kDefaultCamOffsetX, kDefaultCamOffsetY, kDefaultCamOffsetZ,
                    kDefaultCamHeading, kDefaultCamPitch };
    cameraMode = CameraMode::kChase;
}

void ResetChaseCamera(CameraState& cameraState)
{
    cameraState = { kDefaultCamOffsetX, kDefaultCamOffsetY, kDefaultCamOffsetZ,
                    kDefaultCamHeading, kDefaultCamPitch };
}

void UpdateChaseCamera(I3DEngine* engine, ICamera* camera, IModel* carModel,
    float carHeading, CameraState& cameraState, float deltaTime)
{
    if (engine->KeyHeld(Key_Up))    cameraState.offsetZ += kCameraMoveSpeed * deltaTime;
    if (engine->KeyHeld(Key_Down))  cameraState.offsetZ -= kCameraMoveSpeed * deltaTime;
    if (engine->KeyHeld(Key_Left))  cameraState.offsetX -= kCameraMoveSpeed * deltaTime;
    if (engine->KeyHeld(Key_Right)) cameraState.offsetX += kCameraMoveSpeed * deltaTime;

    cameraState.Heading += engine->GetMouseMovementX() * kCameraTurnSpeed;
    cameraState.pitch -= engine->GetMouseMovementY() * kCameraTurnSpeed;
    cameraState.pitch = max(kCameraPitchMin, min(kCameraPitchMax, cameraState.pitch));

    float totalHeading = carHeading + cameraState.Heading;
    float radians = totalHeading * kDegToRad;

    float backX = sinf(radians) * cameraState.offsetZ;
    float backZ = cosf(radians) * cameraState.offsetZ;
    float sideX = cosf(radians) * cameraState.offsetX;
    float sideZ = -sinf(radians) * cameraState.offsetX;

    camera->SetPosition(carModel->GetX() + backX + sideX,
        carModel->GetY() + cameraState.offsetY,
        carModel->GetZ() + backZ + sideZ);
    camera->ResetOrientation();
    camera->RotateY(totalHeading);
    camera->RotateLocalX(cameraState.pitch);
}

void UpdateFirstPersonCamera(ICamera* camera, IModel* carModel, float carHeading)
{
    float radians = carHeading * kDegToRad;
    camera->SetPosition(
        carModel->GetX() + sinf(radians) * kFirstPersonOffsetZ,
        carModel->GetY() + kFirstPersonOffsetY,
        carModel->GetZ() + cosf(radians) * kFirstPersonOffsetZ);
    camera->ResetOrientation();
    camera->RotateY(carHeading);
}

//  NPC FUNCTIONS
void UpdateNpc(IModel* npcModel, float& npcHeading, Vector2& npcVelocity,
    const vector<Vector2>& waypoints, int& waypointIndex,
    float deltaTime, float hoverY)
{
    if (waypoints.empty()) return;

    Vector2 currentPosition = { npcModel->GetX(), npcModel->GetZ() };
    Vector2 targetWaypoint = waypoints[waypointIndex];
    Vector2 direction = (targetWaypoint - currentPosition).Normalized();

    float wantedHeading = atan2f(direction.x, direction.z) * kRadToDeg;
    float HeadingDiff = wantedHeading - npcHeading;

    while (HeadingDiff > kHalfCircleDeg) HeadingDiff -= kFullCircleDeg;
    while (HeadingDiff < -kHalfCircleDeg) HeadingDiff += kFullCircleDeg;

    HeadingDiff = max(-kNpcTurnSpeed * deltaTime, min(kNpcTurnSpeed * deltaTime, HeadingDiff));
    npcHeading += HeadingDiff;

    float   radians = npcHeading * kDegToRad;
    Vector2 forwardVector = { sinf(radians), cosf(radians) };
    npcVelocity = forwardVector * kNpcSpeed;

    npcModel->SetPosition(currentPosition.x + npcVelocity.x * deltaTime,
        hoverY,
        currentPosition.z + npcVelocity.z * deltaTime);
    npcModel->ResetOrientation();
    npcModel->RotateY(npcHeading);

    Vector2 newPosition = { npcModel->GetX(), npcModel->GetZ() };
    if ((targetWaypoint - newPosition).Length() < kNpcWaypointRadius)
        waypointIndex = (waypointIndex + kWaypointIncrement) % static_cast<int>(waypoints.size());
}

void ResetNpc(IModel* npcModel, NpcState& npcState)
{
    npcModel->SetPosition(kNpcStartX, kHoverBaseY, kNpcStartZ);
    npcModel->ResetOrientation();
    npcState = NpcState{};
}

//  PLAYER FUNCTIONS
void ResetPlayer(IModel* playerModel, PlayerState& playerState)
{
    playerModel->SetPosition(kPlayerStartX, kHoverBaseY, kPlayerStartZ);
    playerModel->ResetOrientation();
    playerState = PlayerState{};
}

//  HUD FUNCTIONS
float GetSpeedKmh(const Vector2& velocity)
{
    return velocity.Length() * kMetersPerUnit * kMpsToKmph;
}

int GetRaceProgressScore(int currentLap, int nextCheckpointIndex, int totalCheckpoints)
{
    return (currentLap - kLapNumberOffset) * totalCheckpoints + nextCheckpointIndex;
}

void DrawHUD(IFont* hudFont, IFont* bigFont, IFont* alertFont,
    IFont* hintFont, IFont* bannerFont,
    I3DEngine* engine, GameState gameState, const string& statusMessage,
    float raceTime, int health, int currentLap, int totalLaps,
    int nextCheckpointNumber, int totalCheckpoints,
    const BoostState& boost, int playerPosition,
    const string& winnerMessage, const Vector2& velocity)
{
    const int     screenWidth = engine->GetWidth();
    const int     screenHeight = engine->GetHeight();
    ostringstream textStream;

    hudFont->Draw("LAP  " + to_string(currentLap) + " / " + to_string(totalLaps),
        kHUDMarginX, kHUDMarginY, kWhite);
    hudFont->Draw("CP   " + to_string(nextCheckpointNumber) + " / " + to_string(totalCheckpoints),
        kHUDMarginX, kHUDMarginY + kHUDLineSpacing, kWhite);

    bigFont->Draw("P" + to_string(playerPosition) + " / " + to_string(kNumRacers),
        screenWidth / 2 - kHUDPlayerPosX, kHUDPlayerPosY, kYellow);

    textStream << fixed << setprecision(kTimerPrecision) << raceTime;
    hudFont->Draw("TIME  " + textStream.str(), screenWidth / 2 - kHUDTimeX, kHUDTimeY, kWhite);

    bigFont->Draw(to_string(static_cast<int>(GetSpeedKmh(velocity))) + " KM/H",
        screenWidth - kHUDSpeedX, kHUDSpeedY, kWhite);

    bool isHealthLow = health < kBoostDisabledHealth;
    hudFont->Draw("HEALTH  " + to_string(health),
        kHUDMarginX, screenHeight - kHUDHealthY, isHealthLow ? kRed : kWhite);
    if (isHealthLow)
        alertFont->Draw("BOOST DISABLED", kHUDMarginX, screenHeight - kHUDHealthWarningY, kRed);

    const int boostPosX = screenWidth - kHUDBoostX;
    if (boost.overheated)
    {
        alertFont->Draw("OVERHEAT", boostPosX, screenHeight - kHUDWarningY, kRed);
        textStream.str("");
        textStream << fixed << setprecision(kTimerPrecision) << boost.cooldown;
        hudFont->Draw("COOLDOWN  " + textStream.str() + "S",
            boostPosX, screenHeight - kHUDCooldownY, kWhite);
    }
    else if (boost.active)
    {
        alertFont->Draw("BOOST  ACTIVE", boostPosX, screenHeight - kHUDWarningY, kGreen);
        if (boost.activeTimer >= kBoostWarningTime)
            hudFont->Draw("OVERHEATING SOON", boostPosX, screenHeight - kHUDCooldownY, kRed);
    }
    else if (boost.ready)
    {
        alertFont->Draw("BOOST  READY", boostPosX, screenHeight - kHUDWarningY, kGreen);
    }

    if (!statusMessage.empty())
        hudFont->Draw(statusMessage, screenWidth / 2 - kHUDStatusWidth,
            screenHeight - kHUDStatusY, kBlue);

    hintFont->Draw("[ 1 ] CHASE    [ 2 ] FIRST PERSON    [ R ] RESTART",
        kHUDMarginX, screenHeight - kHUDHintY, kBlack);

    if (gameState == GameState::kRaceComplete)
        bannerFont->Draw(winnerMessage,
            screenWidth / 2 - kHUDBannerWidth,
            screenHeight / 2 - kHUDBannerY, kYellow);
    else if (gameState == GameState::kGameOver)
        bannerFont->Draw("GAME  OVER",
            screenWidth / 2 - kHUDBannerGameOverWidth,
            screenHeight / 2 - kHUDBannerY, kRed);
}

//  SCENE BUILDING
Scene BuildScene(const vector<SceneItem>& sceneItems,
    IMesh* isleMesh, IMesh* wallMesh,
    IMesh* tankMesh1, IMesh* tankMesh2,
    IMesh* checkpointMesh, IMesh* crossMesh,
    IMesh* flareMesh)
{
    Scene scene;

    for (const SceneItem& item : sceneItems)
    {
        if (item.type == kTypeIsle)
        {
            IModel* model = isleMesh->CreateModel(item.x, kModelSpawnY, item.z);
            model->RotateY(item.rotationY);
            model->Scale(kIsleScale);
            scene.isles.push_back(model);
        }
        else if (item.type == kTypeWall)
        {
            IModel* model = wallMesh->CreateModel(item.x, kModelSpawnY, item.z);
            model->RotateY(item.rotationY);
            model->Scale(kWallScale);
            scene.walls.push_back(model);
        }
        else if (item.type == kTypeCheckpoint)
        {
            IModel* model = checkpointMesh->CreateModel(item.x, kModelSpawnY, item.z);
            model->RotateY(item.rotationY);
            model->Scale(kCheckpointScale);
            scene.checkpoints.push_back({ model, item.x, item.z, item.rotationY });
            scene.crosses.push_back({ crossMesh->CreateModel(item.x, kOffscreenY, item.z), 0.0f });
        }
        else if (item.type == kTypeTank1 || item.type == kTypeTank2)
        {
            IMesh* mesh = (item.type == kTypeTank1) ? tankMesh1 : tankMesh2;
            IModel* model = mesh->CreateModel(item.x, kModelSpawnY, item.z);
            model->RotateY(item.rotationY);
            model->Scale(kTankScale);
            scene.tanks.push_back(model);
        }
        else if (item.type == kTypeFlare)
        {
            IModel* model = flareMesh->CreateModel(item.x, kModelSpawnY, item.z);
            scene.flares.push_back({ model, item.x, item.z, 0.0f });
        }
    }

    return scene;
}

//  CROSS MARKER FUNCTIONS
void ShowCrossMarker(CrossMarker& crossMarker, float positionX, float positionZ)
{
    crossMarker.model->SetPosition(positionX, kCrossYOffset, positionZ);
    crossMarker.lifeTimer = kCrossLifetime;
}

void UpdateCrossMarkers(vector<CrossMarker>& crossMarkers, float deltaTime)
{
    for (CrossMarker& marker : crossMarkers)
    {
        if (marker.lifeTimer <= 0.0f) continue;
        marker.lifeTimer -= deltaTime;
        if (marker.lifeTimer <= 0.0f)
            marker.model->SetPosition(marker.model->GetX(), kOffscreenY, marker.model->GetZ());
    }
}

//  FLARE COLLISION PROCESSING
bool ProcessFlareCollisions(float& playerX, float& playerZ, Vector2& playerMomentum,
    vector<FlareBomb>& flares, float deltaTime,
    int& health, string& statusMessage,
    float& damageCooldown,
    Particle particles[], int totalParticles)
{
    bool anyHit = false;

    for (FlareBomb& flare : flares)
    {
        if (flare.cooldownTimer > 0.0f)
        {
            flare.cooldownTimer -= deltaTime;
            continue;
        }

        if (!CheckCollisionSphereSphere(playerX, playerZ, kCarRadius,
            flare.x, flare.z, kFlareRadius))
            continue;

        Vector2 pushDirection = Vector2(playerX - flare.x, playerZ - flare.z).Normalized();
        playerX += pushDirection.x * (kCarRadius + kFlareRadius);
        playerZ += pushDirection.z * (kCarRadius + kFlareRadius);

        float currentSpeed = playerMomentum.Length();
        playerMomentum += pushDirection * (currentSpeed * kFlareBlastMultiplier);

        if (damageCooldown <= 0.0f)
        {
            health = max(kMinHealth, health - kFlareDamage);
            damageCooldown = kDamageCooldown;
            statusMessage = "Hit by bomb! -" + to_string(kFlareDamage) + " HP";
            EmitParticles(particles, totalParticles, flare.x, flare.z, kHoverBaseY);
        }

        flare.cooldownTimer = kFlareCooldown;
        anyHit = true;
    }

    return anyHit;
}

//  FULL GAME RESET
void ResetGame(IModel* playerCarModel, IModel* npcCarModel,
    PlayerState& playerState, NpcState& npcState,
    CameraState& cameraState, CameraMode& cameraMode,
    GameState& gameState,
    string& statusMessage, string& winnerMessage,
    vector<CrossMarker>& crossMarkers, vector<FlareBomb>& flares,
    Particle particles[], int totalParticles,
    SmokeParticle smokeParticles[], int totalSmoke)
{
    ResetPlayer(playerCarModel, playerState);
    ResetNpc(npcCarModel, npcState);
    ResetCamera(cameraState, cameraMode);

    gameState = GameState::kWaitingToStart;
    statusMessage = "Hit Space to Start";
    winnerMessage = "";

    for (CrossMarker& marker : crossMarkers)
        marker.model->SetPosition(marker.model->GetX(), kOffscreenY, marker.model->GetZ());

    for (FlareBomb& flare : flares)
        flare.cooldownTimer = 0.0f;

    for (int i = 0; i < totalParticles; ++i)
    {
        particles[i].alive = false;
        if (particles[i].model)
            particles[i].model->SetPosition(kOriginX, kOffscreenY, kOriginZ);
    }

    // Hide all smoke puffs on reset
    ResetSmokeParticles(smokeParticles, totalSmoke);
}

//  MAIN
int main()
{
    srand(static_cast<unsigned>(time(nullptr)));

    I3DEngine* engine = New3DEngine(kTLX);
    engine->StartFullscreen();
    engine->AddMediaFolder(kMediaFolder);

    //meshes
    IMesh* carMesh = engine->LoadMesh("race2.x");
    IMesh* checkpointMesh = engine->LoadMesh("Checkpoint.x");
    IMesh* isleMesh = engine->LoadMesh("IsleStraight.x");
    IMesh* wallMesh = engine->LoadMesh("Wall.x");
    IMesh* groundMesh = engine->LoadMesh("ground.x");
    IMesh* skyMesh = engine->LoadMesh("Skybox07.x");
    IMesh* tankMesh1 = engine->LoadMesh("TankSmall1.x");
    IMesh* tankMesh2 = engine->LoadMesh("TankSmall2.x");
    IMesh* crossMesh = engine->LoadMesh("Cross.x");
    IMesh* flareMesh = engine->LoadMesh("Flare.x");
    IMesh* quadMesh = engine->LoadMesh("quad.x");

    //fonts
    IFont* hudFont = engine->LoadFont(kFontName, kHUDFontSize);
    IFont* bigFont = engine->LoadFont(kFontName, kBigFontSize);
    IFont* alertFont = engine->LoadFont(kFontName, kAlertFontSize);
    IFont* hintFont = engine->LoadFont(kFontName, kHintFontSize);
    IFont* bannerFont = engine->LoadFont(kFontName, kBannerFontSize);

    //environment
    groundMesh->CreateModel(kOriginX, kGroundY, kOriginZ);
    skyMesh->CreateModel(kOriginX, kSkyY, kOriginZ);

    // scene
    vector<SceneItem> sceneItems;
    if (!LoadSceneFromFile(kSceneFile, sceneItems)) { engine->Delete(); return 1; }

    Scene scene = BuildScene(sceneItems, isleMesh, wallMesh,
        tankMesh1, tankMesh2, checkpointMesh, crossMesh, flareMesh);

    //NPC waypoints
    vector<Vector2> waypoints;
    if (!LoadWaypointsFromFile(kWaypointsFile, waypoints) || waypoints.empty())
    {
        engine->Delete(); return 1;
    }

    //car models
    IModel* playerCarModel = carMesh->CreateModel(kPlayerStartX, kHoverBaseY, kPlayerStartZ);
    playerCarModel->Scale(kCarScale);

    IModel* npcCarModel = carMesh->CreateModel(kNpcStartX, kHoverBaseY, kNpcStartZ);
    npcCarModel->Scale(kCarScale);
    npcCarModel->SetSkin(kNpcSkinFile);

    // Initialise flare
    Particle particles[kNumParticles];
    for (int i = 0; i < kNumParticles; ++i)
    {
        IModel* quad = quadMesh->CreateModel(kOriginX, kOffscreenY, kOriginZ);
        if (quad) { quad->Scale(kParticleScale); quad->SetSkin(kParticleTexture); }
        particles[i] = { quad, Vector3{}, false };
    }

    SmokeParticle smokeParticles[kNumSmokeParticles];
    InitSmokeParticles(smokeParticles, kNumSmokeParticles, quadMesh, playerCarModel);
    float smokeEmitTimer = 0.0f;

    // Initialise camera and game state
    ICamera* camera = engine->CreateCamera(kManual);
    GameState   gameState = GameState::kWaitingToStart;
    CameraMode  cameraMode = CameraMode::kChase;
    float       countdownTimer = 0.0f;
    string      statusMessage = "Hit Space to Start";
    string      winnerMessage = "";
    PlayerState playerState;
    NpcState    npcState;
    CameraState cameraState;
    ResetChaseCamera(cameraState);

    //  MAIN GAME LOOP
    while (engine->IsRunning())
    {
        const float deltaTime = engine->Timer();
        engine->DrawScene();

        // Quit
        if (engine->KeyHit(Key_Escape)) engine->Stop();

        // Restart
        if (engine->KeyHit(kKeyRestart))
        {
            ResetGame(playerCarModel, npcCarModel, playerState, npcState,
                cameraState, cameraMode, gameState,
                statusMessage, winnerMessage,
                scene.crosses, scene.flares,
                particles, kNumParticles,
                smokeParticles, kNumSmokeParticles);
            smokeEmitTimer = 0.0f;
        }

        // Camera mode switching
        if (engine->KeyHit(kKeyCamChase) && cameraMode != CameraMode::kChase)
        {
            cameraMode = CameraMode::kChase;
            ResetChaseCamera(cameraState);
        }
        if (engine->KeyHit(kKeyCamFirst))
            cameraMode = CameraMode::kFirstPerson;

        // Per-frame timers
        if (playerState.damageCooldown > 0.0f) playerState.damageCooldown -= deltaTime;
        UpdateCrossMarkers(scene.crosses, deltaTime);
        UpdateParticles(particles, kNumParticles, deltaTime);

        // Smoke system update (always runs; only emits when health is low)
        UpdateSmokeParticles(smokeParticles, kNumSmokeParticles, deltaTime);

        if (gameState == GameState::kRacing &&
            playerState.health < kBoostDisabledHealth && 
            playerState.health > kMinHealth)              
        {
            smokeEmitTimer -= deltaTime;
            if (smokeEmitTimer <= 0.0f)
            {
                EmitSmokePuff(smokeParticles, kNumSmokeParticles);
                smokeEmitTimer = kSmokeEmitInterval;
            }
        }
        else
        {
            smokeEmitTimer = 0.0f;
        }

        // Hover offsets
        const float playerHoverY = kHoverBaseY + sinf(playerState.raceTime * kHoverFrequency) * kHoverAmplitude;
        const float npcHoverY = kHoverBaseY + sinf(npcState.raceTime * kHoverFrequency) * kHoverAmplitude;

        //  GAME STATE MACHINE
        switch (gameState)
        {
        case GameState::kWaitingToStart:
            if (engine->KeyHit(kKeyStart))
            {
                gameState = GameState::kCounting;
                countdownTimer = kCountdownDuration;
            }
            break;

        case GameState::kCounting:
            countdownTimer -= deltaTime;
            statusMessage = to_string(static_cast<int>(ceilf(countdownTimer)));
            if (countdownTimer <= 0.0f)
            {
                statusMessage = "";
                gameState = GameState::kRacing;
            }
            break;

        case GameState::kRacing:
        {
            playerState.raceTime += deltaTime;
            npcState.raceTime += deltaTime;

            //Boost logic
            BoostState& boost = playerState.boost;

            if (playerState.health < kBoostDisabledHealth)
            {
                boost.active = false;
                boost.ready = false;
                boost.activeTimer = 0.0f;
            }
            else if (boost.overheated)
            {
                boost.cooldown -= deltaTime;
                if (boost.cooldown <= 0.0f)
                {
                    boost.overheated = false;
                    boost.ready = true;
                }
            }
            else
            {
                boost.ready = true;
                if (engine->KeyHeld(kKeyBoost))
                {
                    boost.active = true;
                    boost.activeTimer += deltaTime;
                    if (boost.activeTimer >= kBoostMaxTime)
                    {
                        boost.active = false;
                        boost.overheated = true;
                        boost.cooldown = kBoostCooldownTime;
                        boost.activeTimer = 0.0f;
                    }
                }
                else
                {
                    boost.active = false;
                    boost.activeTimer = 0.0f;
                }
            }

            //Player movement
            float   radians = playerState.Heading * kDegToRad;
            Vector2 forwardVector = { sinf(radians), cosf(radians) };
            Vector2 thrustForce;
            float   leanRoll = 0.0f;
            playerState.targetPitch = 0.0f;

            if (engine->KeyHeld(kKeyThrustForward))
            {
                float magnitude = kThrustForward * (boost.active ? kBoostMultiplier : kNormalSpeedMultiplier);
                thrustForce = thrustForce + forwardVector * magnitude;
                playerState.targetPitch = kPitchAmount;
            }
            if (engine->KeyHeld(kKeyThrustBack))
            {
                thrustForce = thrustForce + forwardVector * (-kThrustBackward);
                playerState.targetPitch = -kPitchAmount;
            }
            if (engine->KeyHeld(kKeyTurnLeft)) { playerState.Heading -= kTurnSpeed * deltaTime; leanRoll = kLeanAmount; }
            if (engine->KeyHeld(kKeyTurnRight)) { playerState.Heading += kTurnSpeed * deltaTime; leanRoll = -kLeanAmount; }

            float   dragMultiplier = boost.overheated ? kDrag * kOverheatDragMult : kDrag;
            Vector2 dragForce = playerState.velocity * (-dragMultiplier);
            playerState.velocity += (thrustForce + dragForce) * deltaTime;

            float maxSpeed = boost.active ? kMaxSpeedBoost : kMaxSpeedNormal;
            if (playerState.velocity.Length() > maxSpeed)
                playerState.velocity = playerState.velocity.Normalized() * maxSpeed;

            playerState.currentPitch += (playerState.targetPitch - playerState.currentPitch)
                * kPitchSmoothing * deltaTime;

            float newX = playerCarModel->GetX() + playerState.velocity.x * deltaTime;
            float newZ = playerCarModel->GetZ() + playerState.velocity.z * deltaTime;

            //Tank collision
            for (IModel* tank : scene.tanks)
            {
                if (!CheckCollisionSphereSphere(newX, newZ, kCarRadius,
                    tank->GetX(), tank->GetZ(), kTankRadius))
                    continue;

                playerState.velocity = playerState.velocity * (-kTankBounce);

                if (playerState.damageCooldown <= 0.0f)
                {
                    playerState.health = max(kMinHealth, playerState.health - kCollisionDamage);
                    playerState.damageCooldown = kDamageCooldown;
                    statusMessage = "Hit tank";
                }
                break;
            }

            //Wall collision
            bool hitWall = false;
            for (IModel* wall : scene.walls)
            {
                if (!CheckCollisionAxisAlignedBox(newX, newZ,
                    wall->GetX(), wall->GetZ(), kWallHalfExtent))
                    continue;

                playerState.velocity = playerState.velocity * (-kBarrierBounce);

                if (playerState.damageCooldown <= 0.0f)
                {
                    playerState.health = max(kMinHealth, playerState.health - kCollisionDamage);
                    playerState.damageCooldown = kDamageCooldown;
                    statusMessage = "Hit wall";
                }
                hitWall = true;
                break;
            }

            playerCarModel->SetPosition(hitWall ? playerCarModel->GetX() : newX,
                playerHoverY,
                hitWall ? playerCarModel->GetZ() : newZ);

            //Checkpoint post collision
            if (playerState.nextCheckpoint < static_cast<int>(scene.checkpoints.size()) &&
                CheckCollisionCheckpointPost(playerCarModel->GetX(), playerCarModel->GetZ(),
                    scene.checkpoints[playerState.nextCheckpoint]))
            {
                playerState.velocity = playerState.velocity * (-kCheckpointBounce);

                if (playerState.damageCooldown <= 0.0f)
                {
                    playerState.health = max(kMinHealth, playerState.health - kCollisionDamage);
                    playerState.damageCooldown = kDamageCooldown;
                    statusMessage = "Hit checkpoint post";
                }
            }

            //   Flare collision  
            if (ProcessFlareCollisions(newX, newZ, playerState.velocity, scene.flares, deltaTime,
                playerState.health, statusMessage, playerState.damageCooldown,
                particles, kNumParticles))
                playerCarModel->SetPosition(newX, playerHoverY, newZ);

            //   Visual orientation  
            playerCarModel->ResetOrientation();
            playerCarModel->RotateY(playerState.Heading);
            playerCarModel->RotateLocalZ(leanRoll);
            playerCarModel->RotateLocalX(playerState.currentPitch);

            //   Checkpoint crossing (player)  
            if (playerState.nextCheckpoint < static_cast<int>(scene.checkpoints.size()) &&
                CheckCollisionPointInCheckpointGap(playerCarModel->GetX(), playerCarModel->GetZ(),
                    scene.checkpoints[playerState.nextCheckpoint]))
            {
                ShowCrossMarker(scene.crosses[playerState.nextCheckpoint],
                    scene.checkpoints[playerState.nextCheckpoint].x,
                    scene.checkpoints[playerState.nextCheckpoint].z);

                playerState.nextCheckpoint += kCheckpointIncrement;
                statusMessage = "Stage " + to_string(playerState.nextCheckpoint) + " complete";

                if (playerState.nextCheckpoint >= static_cast<int>(scene.checkpoints.size()))
                {
                    playerState.nextCheckpoint = 0;
                    playerState.lap += kLapIncrement;

                    if (playerState.lap > kTotalLaps)
                    {
                        winnerMessage = "Player Wins! Time: "
                            + to_string(static_cast<int>(playerState.raceTime)) + "s";
                        gameState = GameState::kRaceComplete;
                    }
                    else
                        statusMessage = "Lap " + to_string(playerState.lap) + " started";
                }
            }

            //   NPC movement update  
            UpdateNpc(npcCarModel, npcState.Heading, npcState.velocity,
                waypoints, npcState.waypointIndex, deltaTime, npcHoverY);

            //   NPC wall collision  
            for (IModel* wall : scene.walls)
            {
                if (!CheckCollisionAxisAlignedBox(npcCarModel->GetX(), npcCarModel->GetZ(),
                    wall->GetX(), wall->GetZ(), kWallHalfExtent))
                    continue;

                npcCarModel->SetPosition(
                    npcCarModel->GetX() - npcState.velocity.x * deltaTime * kNpcWallPushbackFactor,
                    npcHoverY,
                    npcCarModel->GetZ() - npcState.velocity.z * deltaTime * kNpcWallPushbackFactor);

                npcState.waypointIndex = (npcState.waypointIndex + kWaypointIncrement)
                    % static_cast<int>(waypoints.size());
                break;
            }

            //   Checkpoint crossing (NPC)  
            if (npcState.nextCheckpoint < static_cast<int>(scene.checkpoints.size()) &&
                CheckCollisionPointInCheckpointGap(npcCarModel->GetX(), npcCarModel->GetZ(),
                    scene.checkpoints[npcState.nextCheckpoint]))
            {
                npcState.nextCheckpoint += kCheckpointIncrement;

                if (npcState.nextCheckpoint >= static_cast<int>(scene.checkpoints.size()))
                {
                    npcState.nextCheckpoint = 0;
                    npcState.lap += kLapIncrement;

                    if (npcState.lap > kTotalLaps)
                    {
                        winnerMessage = "NPC Wins! Time: "
                            + to_string(static_cast<int>(npcState.raceTime)) + "s";
                        gameState = GameState::kRaceComplete;
                    }
                }
            }

            //   Player vs NPC collision  
            if (CheckCollisionSphereSphere(playerCarModel->GetX(), playerCarModel->GetZ(), kCarRadius,
                npcCarModel->GetX(), npcCarModel->GetZ(), kCarRadius))
            {
                playerCarModel->SetPosition(
                    playerCarModel->GetX() - playerState.velocity.x * deltaTime,
                    playerHoverY,
                    playerCarModel->GetZ() - playerState.velocity.z * deltaTime);

                playerState.velocity = playerState.velocity * (-kNpcBounce);

                if (playerState.damageCooldown <= 0.0f)
                {
                    playerState.health = max(kMinHealth, playerState.health - kCollisionDamage);
                    playerState.damageCooldown = kDamageCooldown;
                    statusMessage = "Hit NPC";
                }
            }

            //   Game over check  
            if (playerState.health <= kMinHealth) gameState = GameState::kGameOver;
            break;
        }

        case GameState::kRaceComplete:
        case GameState::kGameOver:
            playerState.velocity = Vector2{};
            npcState.velocity = Vector2{};
            statusMessage = (gameState == GameState::kRaceComplete)
                ? "Race Complete - Press R to Restart"
                : "GAME OVER - Press R to Restart";
            break;
        }

        // Camera update (frozen on race end)  
        if (gameState != GameState::kRaceComplete && gameState != GameState::kGameOver)
        {
            if (cameraMode == CameraMode::kFirstPerson)
                UpdateFirstPersonCamera(camera, playerCarModel, playerState.Heading);
            else
                UpdateChaseCamera(engine, camera, playerCarModel, playerState.Heading, cameraState, deltaTime);
        }

        //HUD draw  
        int playerScore = GetRaceProgressScore(playerState.lap, playerState.nextCheckpoint,
            static_cast<int>(scene.checkpoints.size()));
        int npcScore = GetRaceProgressScore(npcState.lap, npcState.nextCheckpoint,
            static_cast<int>(scene.checkpoints.size()));
        int position = (playerScore >= npcScore) ? kFirstPlace : kSecondPlace;

        DrawHUD(hudFont, bigFont, alertFont, hintFont, bannerFont,
            engine, gameState, statusMessage,
            playerState.raceTime, playerState.health,
            playerState.lap, kTotalLaps,
            playerState.nextCheckpoint + kCheckpointDisplayOffset,
            static_cast<int>(scene.checkpoints.size()),
            playerState.boost, position, winnerMessage, playerState.velocity);
    }

    engine->Delete();
}