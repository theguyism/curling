/*-----------------------------------------------------------
  Simulation Header File
  -----------------------------------------------------------*/
#include"vecmath.h"

/*-----------------------------------------------------------
  Macros
  -----------------------------------------------------------*/
#define TABLE_X			(0.6f) 
#define TABLE_Z			(1.2f)
#define BALL_RADIUS		(0.03f)
#define BALL_MASS		(0.1f)
#define TWO_PI			(6.2832f)
#define	SIM_UPDATE_MS	(10)
#define NUM_BALLS		(1)		
#define NUM_PLAYERS	(2)
/*-----------------------------------------------------------
  plane normals
  -----------------------------------------------------------*/
extern vec2	gPlaneNormal_Left;
extern vec2	gPlaneNormal_Top;
extern vec2	gPlaneNormal_Right;
extern vec2	gPlaneNormal_Bottom;

/*-----------------------------------------------------------
  ball class
  -----------------------------------------------------------*/

class ball
{
	static int ballIndexCnt;
public:
	vec2	position;
	vec2	velocity;
	float	radius;
	float	mass;
	int		index;
	int	touched;

	ball(): position(0.0), velocity(0.0), radius(BALL_RADIUS), 
		mass(BALL_MASS) {index = ballIndexCnt++; Reset();}
	
	void Reset(void);
	void ApplyImpulse(vec2 imp);
	void ApplyFrictionForce(int ms);
	void DoPlaneCollisions(void);
	void hitplane();
	void DoBallCollision(ball &b);
	void Update(int ms);
	
	bool HasHitPlane1(void) const;
	bool HasHitPlane2(void) const;
	bool HasHitPlane3(void) const;
	bool HasHitPlane4(void) const;
	bool HasHitBall(const ball &b) const;

	void HitPlane1(void);
	void HitPlane2(void);
	void HitPlane3(void);
	void HitPlane4(void);
	void HitBall(ball &b);
};

class player {
	
public:
	static int playerIndex;
	int score;
	int index;
	player() : score(0) {
		index = playerIndex++;
	}
	//void getPlayer(int playerI);
};

/*-----------------------------------------------------------
  table class
  ---------------------------------------------jjjjjjjjjjjjjjjjjjjjjjjjjj--------------*/
class table
{
public:
	ball balls[NUM_BALLS];	
	void Update(int ms);	
	bool AnyBallsMoving(void) const;
	player players[NUM_PLAYERS];
	int	touched;
};

/*-----------------------------------------------------------
  global table
  -----------------------------------------------------------*/
extern table gTable;
