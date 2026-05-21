#include <windows.h>
#include <GL/glut.h>
#include <cmath>

#define PI 3.14159265358979323846
float cloudPosition = -1.2f;
float wheelAngle = 0.0f;
float waveTime = 0.0f;
float cloudSpeed = 0.002f;
bool isDay = true;
bool isPaused = false;
float smallBoatX = 2.5f;
float smallBoatY = -0.15f;
float smallBoatSpeed = 0.003f;
float smallBoatScale = 0.3f;

///Sunglow
void initGL()
{

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void drawSquare(float cx, float cy, float size)
{
    float s = size / 2;
    glBegin(GL_POLYGON);
    glVertex2f(cx - s, cy - s);
    glVertex2f(cx + s, cy - s);
    glVertex2f(cx + s, cy + s);
    glVertex2f(cx - s, cy + s);
    glEnd();
}

void drawCircle(float x, float y, float radius)
{
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 100; i++)
    {
        float angle = 2.0f * 3.1415926f * i / 100;
        glVertex2f(x + radius * cosf(angle),
                   y + radius * sinf(angle));
    }
    glEnd();
}


///Moon
void drawCrescentMoon(float x, float y, float r)
{

    glColor3f(1.0f, 0.98f, 0.85f);
    drawCircle(x, y, r);

    glColor3f(0.0f, 0.0f, 0.2f);
    drawCircle(x + r * 0.35f, y + r * 0.05f, r * 0.9f);
}

///Cloud
void drawCloud(float x, float y)
{
    if(isDay)
        glColor3f(1.0f, 1.0f, 1.0f);     // white cloud
    else
        glColor3f(0.6f, 0.6f, 0.7f);     // dark cloud

    drawCircle(x, y, 0.10f);
    drawCircle(x+0.10f, y+0.04f, 0.11f);
    drawCircle(x+0.20f, y,       0.10f);
    drawCircle(x+0.07f, y-0.04f, 0.08f);
    drawCircle(x+0.17f, y-0.04f, 0.08f);
}


///Star
void drawStars()
{
    glPointSize(2.5f);
    glBegin(GL_POINTS);
    glColor3f(1,1,1);

    // Left side
    glVertex2f(-1.8f, 0.9f);
    glVertex2f(-1.6f, 0.7f);
    glVertex2f(-1.5f, 0.8f);
    glVertex2f(-1.3f, 0.6f);
    glVertex2f(-1.2f, 0.9f);
    glVertex2f(-1.1f, 0.75f);
    glVertex2f(-0.9f, 0.85f);
    glVertex2f(-0.8f, 0.65f);
    glVertex2f(-0.7f, 0.9f);

    // Middle
    glVertex2f(-0.5f, 0.7f);
    glVertex2f(-0.4f, 0.85f);
    glVertex2f(-0.3f, 0.6f);
    glVertex2f(-0.2f, 0.75f);
    glVertex2f( 0.0f, 0.9f);
    glVertex2f( 0.1f, 0.7f);
    glVertex2f( 0.2f, 0.85f);
    glVertex2f( 0.3f, 0.6f);
    glVertex2f( 0.4f, 0.75f);
    glVertex2f( 0.5f, 0.9f);

    // Right
    glVertex2f( 0.7f, 0.8f);
    glVertex2f( 0.8f, 0.6f);
    glVertex2f( 0.9f, 0.9f);
    glVertex2f( 1.0f, 0.7f);
    glVertex2f( 1.1f, 0.85f);
    glVertex2f( 1.2f, 0.6f);
    glVertex2f( 1.3f, 0.75f);
    glVertex2f( 1.4f, 0.9f);
    glVertex2f( 1.5f, 0.65f);
    glVertex2f( 1.7f, 0.8f);

    // Extra small scattered stars
    glVertex2f(-0.6f, 0.55f);
    glVertex2f(-0.1f, 0.6f);
    glVertex2f( 0.6f, 0.55f);
    glVertex2f( 1.6f, 0.6f);
    glVertex2f(-1.0f, 0.55f);
    glVertex2f( 0.9f, 0.55f);

    glEnd();
}


///Baloons
void drawBalloons(float x, float y)
{
    glPushMatrix();
    glTranslatef(x, y, 0);

    float jointX = 0.09f;
    float jointY = 0.0f;

    // Strings
    glColor3f(0,0,0);
    glBegin(GL_LINES);
    glVertex2f(jointX, jointY);
    glVertex2f(0.10f, 0.22f);
    glVertex2f(jointX, jointY);
    glVertex2f(0.14f, 0.26f);
    glVertex2f(jointX, jointY);
    glVertex2f(0.18f, 0.23f);
    glVertex2f(jointX, jointY);
    glVertex2f(0.22f, 0.27f);
    glVertex2f(jointX, jointY);
    glVertex2f(0.26f, 0.24f);
    glEnd();

    // Balloons
    float r = 0.02f;

    glColor3f(1,0,0);
    drawCircle(0.10f, 0.22f, r);

    glColor3f(0,1,0);
    drawCircle(0.14f, 0.26f, r);

    glColor3f(0,0,1);
    drawCircle(0.18f, 0.23f, r);

    glColor3f(1,1,0);
    drawCircle(0.22f, 0.27f, r);

    glColor3f(1,0,1);
    drawCircle(0.26f, 0.24f, r);

    glPopMatrix();
}

///Man1
void drawMan(float x, float y,
             float heightScale,
             float skinR, float skinG, float skinB,
             float shirtR, float shirtG, float shirtB)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(1.0f, heightScale, 1.0f);   // ⭐ height control

    // Head
    glColor3f(skinR, skinG, skinB);
    drawCircle(0.0f, 0.08f, 0.035f);

    // Eyes
    glColor3f(0, 0, 0);
    drawCircle(-0.012f, 0.085f, 0.004f);
    drawCircle( 0.012f, 0.085f, 0.004f);

    // Mouth
    glBegin(GL_LINES);
    glVertex2f(-0.01f, 0.07f);
    glVertex2f( 0.01f, 0.07f);
    glEnd();

    // Ears
    glColor3f(skinR, skinG, skinB);
    drawCircle(-0.04f, 0.08f, 0.008f);
    drawCircle( 0.04f, 0.08f, 0.008f);

    // Hair
    glColor3f(0.1f, 0.05f, 0.02f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.035f, 0.105f);
    glVertex2f( 0.035f, 0.105f);
    glVertex2f( 0.025f, 0.13f);
    glVertex2f(-0.025f, 0.13f);
    glEnd();

    // Shirt
    glColor3f(shirtR, shirtG, shirtB);
    glBegin(GL_POLYGON);
    glVertex2f(-0.03f,  0.04f);
    glVertex2f( 0.03f,  0.04f);
    glVertex2f( 0.03f, -0.08f);
    glVertex2f(-0.03f, -0.08f);
    glEnd();

    // Arms
    glColor3f(skinR, skinG, skinB);
    glBegin(GL_POLYGON);
    glVertex2f(-0.03f,  0.02f);
    glVertex2f(-0.09f,  0.00f);
    glVertex2f(-0.085f, -0.02f);
    glVertex2f(-0.03f, -0.01f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0.03f,  0.02f);
    glVertex2f(0.09f,  0.00f);
    glVertex2f(0.085f, -0.02f);
    glVertex2f(0.03f, -0.01f);
    glEnd();

    // Legs
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.025f, -0.08f);
    glVertex2f(-0.005f, -0.08f);
    glVertex2f(-0.02f,  -0.20f);
    glVertex2f(-0.04f,  -0.20f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0.005f, -0.08f);
    glVertex2f(0.025f, -0.08f);
    glVertex2f(0.04f,  -0.20f);
    glVertex2f(0.02f,  -0.20f);
    glEnd();

    glPopMatrix();
}


///Land
void drawLand()
{
 glBegin(GL_POLYGON);
 // Upper land (lighter shade)
 glColor3f(0.7f, 0.55f, 0.25f);
 glVertex2f(-1.0f,-1.5);
 glColor3f(0.65f, 0.5f, 0.22f);
 glVertex2f(-2.0f, -1.0f);
 glColor3f(0.06f, 0.45f, 0.2f);
 glVertex2f(-1.0f, -0.3f);
 glColor3f(0.55f, 0.4f, 0.18f);
 glVertex2f(2.0f, 0.0f);
 // bottom land (darker shade)
 glColor3f(0.4f, 0.28f, 0.12f);
 glVertex2f(2.0f, -1.0f);
  glColor3f(0.35f, 0.25f, 0.1f);
  glVertex2f(-2.0f, -1.0f);
  glEnd();
}
  ///River
void drawRiver()
{
    glBegin(GL_POLYGON);

    // Top (lighter – reflection)
    glColor3f(0.3f, 0.7f, 1.0f);
    glVertex2f(-2, 0.0f);
    glVertex2f( 2, 0.0f);

    // Bottom (darker – depth)
    glColor3f(0.0f, 0.3f, 0.6f);
    glVertex2f( 2, -1.0f);
    glVertex2f(-2, -1.0f);

    glEnd();
}


      ///SMALL_BOAT
void drawSmallBoat(float x, float y)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(smallBoatScale, smallBoatScale, 1.0f);   // 🔽 smaller size

    // Boat body
    glColor3f(0.45f, 0.22f, 0.05f);
    glBegin(GL_POLYGON);
    glVertex2f(-1.3f, 0.15f);
    glVertex2f(-1.2f, 0.05f);
    glVertex2f(-0.9f, 0.05f);
    glVertex2f(-0.8f, 0.15f);
    glEnd();

    // Upper part
    glColor3f(0.85f, 0.6f, 0.25f);
    glBegin(GL_POLYGON);
    glVertex2f(-1.2f, 0.15f);
    glVertex2f(-1.18f, 0.21f);
    glVertex2f(-0.92f, 0.21f);
    glVertex2f(-0.9f, 0.15f);
    glEnd();

    glPopMatrix();
}


void drawRect(float x1, float y1, float x2, float y2)
{
    glBegin(GL_POLYGON);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
}

//
void drawGlowLight(float x, float y, float r)
{
    // Outer glow layers (transparent)
    for (int i = 6; i >= 1; i--)
    {
        float alpha = 0.08f * i;          // stronger near center
        glColor4f(1.0f, 0.9f, 0.3f, alpha);
        drawCircle(x, y, r * (0.35f * i));
    }

    // Inner bright bulb
    glColor3f(1.0f, 1.0f, 0.7f);
    drawCircle(x, y, r);
}

void drawText(float x, float y, const char* text, void* font = GLUT_BITMAP_HELVETICA_12)
{
    glRasterPos2f(x, y);
    for (const char* c = text; *c; c++)
        glutBitmapCharacter(font, *c);
}

// STALL
void drawStall(float x, float y, const char* name)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    // Pillars
    glColor3f(0.5f, 0.3f, 0.1f);
    drawRect(-0.12f, 0.02f, -0.10f, -0.15f);
    drawRect( 0.10f, 0.02f,  0.12f, -0.15f);

    // Roof
    glColor3f(0.9f, 0.7f, 0.3f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.15f, 0.0f);
    glVertex2f( 0.15f, 0.0f);
    glVertex2f( 0.12f, 0.02f);
    glVertex2f(-0.12f, 0.02f);
    glEnd();

    // Counter
    glColor3f(0.6f, 0.35f, 0.15f);
    drawRect(-0.12f, -0.12f, 0.12f, -0.25f);

    // Stall name on counter (inside the brown area)
    glColor3f(1.0f, 1.0f, 1.0f);
    drawText(-0.095f, -0.20f, name, GLUT_BITMAP_HELVETICA_12);

    // LIGHTS
    if (!isDay)
    {
        // Hanging wire line
        glColor3f(0.2f, 0.15f, 0.05f);
        glLineWidth(2.0f);
        glBegin(GL_LINES);
        glVertex2f(-0.11f, 0.01f);
        glVertex2f( 0.11f, 0.01f);
        glEnd();
        glLineWidth(1.0f);

         float flicker = 0.85f + 0.15f * sin(waveTime * 6.0f);

        // 3 bulbs
        glColor4f(1.0f, 0.95f, 0.3f, flicker);
        drawGlowLight(-0.08f, 0.01f, 0.012f);
        drawGlowLight( 0.00f, 0.01f, 0.012f);
        drawGlowLight( 0.08f, 0.01f, 0.012f);
    }

    glPopMatrix();
}



// TREEE
void drawTree(float x, float y)
{
    glColor3f(0.55f, 0.27f, 0.07f);
    glBegin(GL_POLYGON);
    glVertex2f(x - 0.02f, y);
    glVertex2f(x + 0.02f, y);
    glVertex2f(x + 0.02f, y + 0.2f);
    glVertex2f(x - 0.02f, y + 0.2f);
    glEnd();

    glColor3f(0.0f, 0.5f, 0.0f);
    drawCircle(x, y + 0.22f, 0.05f);
    drawCircle(x - 0.03f, y + 0.18f, 0.05f);
    drawCircle(x + 0.03f, y + 0.18f, 0.05f);
}
///FerrisWheel
void drawFerrisWheel(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    float radius = 0.5f;

    //ROTATING WHEEL
    glPushMatrix();
    glRotatef(wheelAngle, 0, 0, 1);

    // Outer circle
    glColor3f(0.9f, 0.2f, 0.2f);
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    for(int i=0; i<360; i++)
    {
        float a = i * PI / 180;
        glVertex2f(cos(a)*radius, sin(a)*radius);
    }
    glEnd();

    // Spokes
    glColor3f(0.95f, 0.75f, 0.4f);
    glBegin(GL_LINES);
    for(int i=0; i<12; i++)
    {
        float a = i * 2 * PI / 12;
        glVertex2f(0,0);
        glVertex2f(cos(a)*radius, sin(a)*radius);
    }
    glEnd();

    // Center hub
    glColor3f(1.0f, 0.6f, 0.3f);
    drawCircle(0,0,0.06f);

    //CABINS
    float colors[6][3] =
    {
        {1,0,0},{1,1,0},{0,1,0},
        {0,0,1},{1,0,1},{0,1,1}
    };

    for(int i=0; i<12; i++)
    {
        float a = i * 2 * PI / 12;
        float cx = cos(a)*radius;
        float cy = sin(a)*radius;

        glPushMatrix();
        glTranslatef(cx, cy, 0);


        glRotatef(-wheelAngle, 0, 0, 1);

        glColor3fv(colors[i % 6]);
        drawSquare(0, -0.08f, 0.09f);
        glPopMatrix();
    }

    glPopMatrix();

    //STAND
    glColor3f(0.6f, 0.2f, 0.2f);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2f(-0.3f, -0.65f);
    glVertex2f(0, 0);
    glVertex2f( 0.3f, -0.65f);
    glVertex2f(0, 0);
    glEnd();

    // Base
    glBegin(GL_POLYGON);
    glVertex2f(-0.4f, -0.65f);
    glVertex2f( 0.4f, -0.65f);
    glVertex2f( 0.4f, -0.7f);
    glVertex2f(-0.4f, -0.7f);
    glEnd();

    glPopMatrix();
}


///Grass

void drawGrassShape(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    glBegin(GL_POLYGON);

    // Bottom (dark shade)
    glColor3f(0.2f, 0.45f, 0.15f);
    glVertex2f(-0.6f, 0.0f);
    glVertex2f( 0.6f, 0.0f);

    // medium shade
    glColor3f(0.35f, 0.65f, 0.25f);
    glVertex2f( 0.45f, 0.25f);
    glVertex2f( 0.30f, 0.15f);
    glVertex2f( 0.20f, 0.40f);
    glVertex2f( 0.05f, 0.20f);

    // light highlight
    glColor3f(0.55f, 0.85f, 0.35f);
    glVertex2f( 0.00f, 0.55f);


    glColor3f(0.35f, 0.65f, 0.25f);
    glVertex2f(-0.10f, 0.30f);
    glVertex2f(-0.25f, 0.45f);
    glVertex2f(-0.35f, 0.20f);
    glVertex2f(-0.50f, 0.30f);

    // Back to base (dark)
    glColor3f(0.2f, 0.45f, 0.15f);
    glVertex2f(-0.6f, 0.0f);

    glEnd();

    glPopMatrix();
}

//Bush
void drawBush(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    // Back shadow layer
    glColor3f(0.15f, 0.35f, 0.18f);
    drawCircle(-0.25f, 0.05f, 0.28f);
    drawCircle( 0.00f, 0.10f, 0.32f);
    drawCircle( 0.30f, 0.05f, 0.26f);

    // Middle layer
    glColor3f(0.25f, 0.50f, 0.25f);
    drawCircle(-0.30f, 0.00f, 0.26f);
    drawCircle( 0.00f, 0.05f, 0.30f);
    drawCircle( 0.30f, 0.00f, 0.24f);

    //  Highlight top layer
    glColor3f(0.35f, 0.65f, 0.35f);
    drawCircle(-0.15f, 0.12f, 0.22f);
    drawCircle( 0.15f, 0.15f, 0.24f);

    glPopMatrix();
}

void drawBigTree(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    // TRUNK
    glColor3f(0.45f, 0.25f, 0.10f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.1f, -0.2f);
    glVertex2f( 0.1f, -0.2f);
    glVertex2f( 0.08f, 0.5f);
    glVertex2f(-0.08f, 0.5f);
    glEnd();

    // Trunk highlight
    glColor3f(0.35f, 0.20f, 0.08f);
    glBegin(GL_POLYGON);
    glVertex2f(0.00f, -0.2f);
    glVertex2f(0.1f, -0.2f);
    glVertex2f(0.08f, 0.5f);
    glVertex2f(0.04f, 0.5f);
    glEnd();

    glPushMatrix();
    glTranslatef(0.0f, 0.8f, 0.0f);

    // Highlight layer
    glColor3f(0.35f, 0.70f, 0.30f);
    drawCircle(-0.55f, 0.1f, 0.32f);
    drawCircle( 0.05f, 0.12f, 0.42f);
    drawCircle( 0.38f, 0.05f, 0.32f);

    // Middle layer
    glColor3f(0.20f, 0.50f, 0.22f);
    drawCircle(-0.45f, 0.05f, 0.35f);
    drawCircle( 0.00f,  0.05f, 0.45f);
    drawCircle( 0.45f, 0.05f, 0.32f);
    /*
        // Highlight top layer
        glColor3f(0.10f, 0.30f, 0.15f);
        drawCircle(-0.20f, 0.22f, 0.28f);
        drawCircle( 0.20f, 0.25f, 0.30f);
    */
    glPopMatrix();

    glPopMatrix();
}

void drawHome(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    // HOUSE BODY
    glColor3f(0.85f, 0.55f, 0.35f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.4f, -0.3f);
    glVertex2f( 0.4f, -0.3f);
    glVertex2f( 0.4f,  0.2f);
    glVertex2f(-0.4f,  0.2f);
    glEnd();

    // ROOF
    glColor3f(0.6f, 0.15f, 0.15f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.45f, 0.2f);
    glVertex2f( 0.45f, 0.2f);
    glVertex2f( 0.0f,  0.55f);
    glEnd();

    /* ===== DOOR ===== */
    glColor3f(0.35f, 0.20f, 0.10f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.08f, -0.3f);
    glVertex2f( 0.08f, -0.3f);
    glVertex2f( 0.08f,  0.0f);
    glVertex2f(-0.08f,  0.0f);
    glEnd();

    /* ===== LEFT WINDOW ===== */
    glColor3f(0.75f, 0.9f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.30f, -0.05f);
    glVertex2f(-0.15f, -0.05f);
    glVertex2f(-0.15f,  0.08f);
    glVertex2f(-0.30f,  0.08f);
    glEnd();

    /* ===== RIGHT WINDOW ===== */
    glBegin(GL_POLYGON);
    glVertex2f(0.15f, -0.05f);
    glVertex2f(0.30f, -0.05f);
    glVertex2f(0.30f,  0.08f);
    glVertex2f(0.15f,  0.08f);
    glEnd();

    /* ===== WINDOW LINES ===== */
    glColor3f(0.3f, 0.3f, 0.3f);
    glLineWidth(2);
    glBegin(GL_LINES);
    // left window
    glVertex2f(-0.225f, -0.05f);
    glVertex2f(-0.225f,  0.08f);
    glVertex2f(-0.30f,  0.015f);
    glVertex2f(-0.15f,  0.015f);

    // right window
    glVertex2f(0.225f, -0.05f);
    glVertex2f(0.225f,  0.08f);
    glVertex2f(0.15f,   0.015f);
    glVertex2f(0.30f,   0.015f);
    glEnd();

    glPopMatrix();
}


void drawSunWithGlow(float x, float y, float radius)
{
    //  Inner bright sun
    glColor3f(1.0f, 0.85f, 0.1f);   // realistic yellow
    drawCircle(x, y, radius);

    //  Outer soft glow layers
    for (int i = 1; i <= 5; i++)
    {
        float alpha = 0.12f - i * 0.02f;   // fade out
        glColor4f(1.0f, 0.8f, 0.2f, alpha);
        drawCircle(x, y, radius + i * 0.05f);
    }
}

void drawNightShade()
{
    glColor4f(0.0f, 0.0f, 0.2f, 0.6f);
    glBegin(GL_POLYGON);
    glVertex2f(-2, -2);
    glVertex2f( 2, -2);
    glVertex2f( 2,  2);
    glVertex2f(-2,  2);
    glEnd();
}

void drawBaby(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    // Head
    glColor3f(1.0, 0.85, 0.7);
    drawCircle(0.0f, 0.4f, 0.2f);

    // Eyes
    glColor3f(1,1,1);
    drawCircle(-0.07f, 0.45f, 0.04f);
    drawCircle( 0.07f, 0.45f, 0.04f);

    glColor3f(0,0,0);
    drawCircle(-0.07f, 0.45f, 0.015f);
    drawCircle( 0.07f, 0.45f, 0.015f);

    // Nose
    glColor3f(0.9, 0.7, 0.6);
    drawCircle(0.0f, 0.38f, 0.02f);

    // Mouth
    glColor3f(0,0,0);
    glBegin(GL_LINES);
    glVertex2f(-0.05f, 0.33f);
    glVertex2f( 0.05f, 0.33f);
    glEnd();

    // Body
    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
    glVertex2f(-0.15f, 0.2f);
    glVertex2f( 0.15f, 0.2f);
    glVertex2f( 0.15f,-0.1f);
    glVertex2f(-0.15f,-0.1f);
    glEnd();

    // Shorts
    glColor3f(1,1,0);
    glBegin(GL_POLYGON);
    glVertex2f(-0.15f,-0.1f);
    glVertex2f( 0.15f,-0.1f);
    glVertex2f( 0.12f,-0.25f);
    glVertex2f(-0.12f,-0.25f);
    glEnd();

    // Arms
    glColor3f(0.9,0.7,0.5);
    glBegin(GL_POLYGON);
    glVertex2f(-0.25f, 0.15f);
    glVertex2f(-0.15f, 0.15f);
    glVertex2f(-0.15f, 0.05f);
    glVertex2f(-0.25f, 0.05f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0.15f, 0.15f);
    glVertex2f(0.25f, 0.15f);
    glVertex2f(0.25f, 0.05f);
    glVertex2f(0.15f, 0.05f);
    glEnd();

    // Legs
    glColor3f(0,0,0);
    glBegin(GL_POLYGON);
    glVertex2f(-0.08f,-0.25f);
    glVertex2f(-0.02f,-0.25f);
    glVertex2f(-0.02f,-0.45f);
    glVertex2f(-0.08f,-0.45f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0.02f,-0.25f);
    glVertex2f(0.08f,-0.25f);
    glVertex2f(0.08f,-0.45f);
    glVertex2f(0.02f,-0.45f);
    glEnd();

    // Shoes
    glColor3f(1,0.8,0);
    drawCircle(-0.05f, -0.47f, 0.04f);
    drawCircle( 0.05f, -0.47f, 0.04f);

    glPopMatrix();
}

void drawBabi(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    //HAIR
    glColor3f(0.15f, 0.08f, 0.03f);

    //Main hair cap
    drawCircle(0.0f, 0.42f, 0.15f);

    //Forehead cut
    glColor3f(1.0f, 0.83f, 0.65f);
    drawCircle(0.0f, 0.38f, 0.12f);

    //Side swoop
    glColor3f(0.15f, 0.08f, 0.03f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.12f, 0.44f);
    glVertex2f(-0.02f, 0.44f);
    glVertex2f(-0.05f, 0.36f);
    glVertex2f(-0.12f, 0.36f);
    glEnd();


    //FACE
    glColor3f(1.0f, 0.83f, 0.65f);
    drawCircle(0.0f, 0.34f, 0.14f);

    // Eyes
    glColor3f(0,0,0);
    drawCircle(-0.04f, 0.36f, 0.01f);
    drawCircle( 0.04f, 0.36f, 0.01f);

    // Mouth
    glBegin(GL_LINES);
    glVertex2f(-0.02f, 0.31f);
    glVertex2f( 0.02f, 0.31f);
    glEnd();


    // Body
    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
    glVertex2f(-0.15f, 0.2f);
    glVertex2f( 0.15f, 0.2f);
    glVertex2f( 0.15f,-0.1f);
    glVertex2f(-0.15f,-0.1f);
    glEnd();

    //Shorts
    glColor3f(1,1,0);
    glBegin(GL_POLYGON);
    glVertex2f(-0.15f,-0.1f);
    glVertex2f( 0.15f,-0.1f);
    glVertex2f( 0.12f,-0.25f);
    glVertex2f(-0.12f,-0.25f);
    glEnd();


// ---------- ARMS (BIGGER & BODY-ALIGNED) ----------
    glColor3f(1.0f, 0.83f, 0.65f);

// Left Arm
    glBegin(GL_POLYGON);
    glVertex2f(-0.15f, 0.20f);   // top (body line)
    glVertex2f(-0.25f, 0.20f);   // more width
    glVertex2f(-0.3f, 0.00f);   // longer down
    glVertex2f(-0.2f, 0.00f);
    glEnd();

// Right Arm
    glBegin(GL_POLYGON);
    glVertex2f( 0.15f, 0.20f);
    glVertex2f( 0.25f, 0.20f);
    glVertex2f( 0.3f, 0.00f);
    glVertex2f( 0.2f, 0.00f);
    glEnd();



    // Legs
    glColor3f(0,0,0);
    glBegin(GL_POLYGON);
    glVertex2f(-0.08f,-0.25f);
    glVertex2f(-0.02f,-0.25f);
    glVertex2f(-0.02f,-0.45f);
    glVertex2f(-0.08f,-0.45f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0.02f,-0.25f);
    glVertex2f(0.08f,-0.25f);
    glVertex2f(0.08f,-0.45f);
    glVertex2f(0.02f,-0.45f);
    glEnd();

    // Shoes
    glColor3f(1,0.8,0);
    drawCircle(-0.05f, -0.47f, 0.04f);
    drawCircle( 0.05f, -0.47f, 0.04f);

    glPopMatrix();
}

    ///DISPLAY_FUNCTION

void display()
{
    if(isDay)
        glClearColor(0.5f, 0.8f, 1.0f, 1.0f);
    else
        glClearColor(0.05f, 0.05f, 0.2f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // ===== BASE SCENE =====
    drawRiver();
    drawSmallBoat(smallBoatX, smallBoatY);
    drawLand();

    drawGrassShape(0.6, -0.5, 0.09f);
    drawGrassShape(0.8, -0.6, 0.09f);
    drawGrassShape(0.10, -0.7, 0.09f);
    drawGrassShape(0.12, -0.5, 0.09f);
    drawGrassShape(0.15, -0.4, 0.09f);
    drawGrassShape(1.10, -0.7, 0.09f);
    drawGrassShape(1.0, -0.5, 0.09f);
    drawGrassShape(1.3, -0.6, 0.09f);
    drawGrassShape(1.55, -0.5, 0.09f);
    drawGrassShape(1.25, -0.7, 0.09f);
    drawGrassShape(-0.4, -0.7, 0.09f);
    drawGrassShape(-0.8, -0.4, 0.09f);
    drawGrassShape(-0.85, -0.8, 0.09f);


    drawMan(0.05f, -0.2f, 0.8f,  1.0f,0.8f,0.6f,  0.2f,0.2f,0.8f);
    drawMan(0.3f, -0.2f, 0.8f,  1.0f,0.8f,0.6f,  2.0f,0.2f,0.5f);
    drawMan(-0.3f, -0.4f, 0.8f,   0.8f,0.6f,0.4f,  0.8f,0.2f,0.2f);

    drawBabi(0.0f, -0.5f, 0.2f);
    drawBalloons(-0.3f, -0.4f);
    drawBalloons(-0.3f, -0.4f);

    drawBigTree(-0.8f, 0.03f, 0.15f);
    drawBigTree(0.8f, 0.03f, 0.15f);
    drawBigTree(0.0f, 0.03f, 0.15f);

    drawBaby(0.2f, -0.4f, 0.2f);

    // Man without balloons
    //drawMan(0.4f, -0.4f);

    drawBaby( 0.2f, -0.4f, 0.2f);

    if(isDay)
    {

    }

    // Upper grass line
    drawGrassShape( 0.1, 0.0, 0.07f);
    drawGrassShape( 0.3, 0.0, 0.07f);
    drawGrassShape( 0.4, 0.0, 0.07f);
    drawGrassShape( 0.5, 0.0, 0.07f);
    drawGrassShape( 0.6, 0.0, 0.07f);
    drawGrassShape( 0.7, 0.0, 0.07f);
    drawGrassShape( 0.9, 0.0, 0.07f);
    drawGrassShape( 1.0, 0.0, 0.07f);
    drawGrassShape( 1.1, 0.0, 0.11f);
    drawGrassShape( 1.2, 0.0, 0.09f);
    drawGrassShape( 1.3, 0.0, 0.09f);
    drawGrassShape( 1.4, 0.0, 0.09f);
    drawGrassShape( 1.5, 0.0, 0.09f);
    drawGrassShape( 1.6, 0.0, 0.07f);
    drawGrassShape( 1.7, 0.0, 0.07f);
    drawGrassShape( 1.8, 0.0, 0.07f);
    drawGrassShape( 1.9, 0.0, 0.07f);
    drawGrassShape( 2.0, 0.0, 0.07f);

    drawGrassShape(-0.1, 0.0, 0.08f);
    drawGrassShape(-0.2, 0.0, 0.09f);
    drawGrassShape(-0.3, 0.0, 0.07f);
    drawGrassShape(-0.4, 0.0, 0.07f);
    drawGrassShape(-0.5, 0.0, 0.07f);
    drawGrassShape(-0.6, 0.0, 0.07f);
    drawGrassShape(-0.7, 0.0, 0.07f);
    drawGrassShape(-0.9, 0.0, 0.07f);
    drawGrassShape(-1.0, 0.0, 0.07f);
    drawGrassShape(-1.1, 0.0, 0.07f);
    drawGrassShape(-1.2, 0.0, 0.07f);
    drawGrassShape(-1.3, 0.0, 0.07f);
    drawGrassShape(-1.4, 0.0, 0.07f);
    drawGrassShape(-1.5, 0.0, 0.07f);
    drawGrassShape(-2.1, 0.0, 0.07f);

    drawGrassShape(-1.6, 0.0, 0.09f);
    drawGrassShape(-1.7, 0.0, 0.09f);
    drawGrassShape(-1.8, 0.0, 0.07f);
    drawGrassShape(-1.9, 0.0, 0.07f);
    drawGrassShape(-2.0, 0.0, 0.07f);
    drawGrassShape(-2.2, 0.0, 0.11f);
    drawGrassShape(-2.3, 0.0, 0.09f);

    // ===== BUSH/HOUSES =====

    drawHome(0.4f, 0.03f, 0.1f);
    drawHome(0.6f, 0.03f, 0.1f);

    drawBigTree(1.8f, -0.4f, 0.7f);
    drawFerrisWheel(-0.8f, -0.1, 0.75f);
    // SKY OBJECTS
    if(isDay)
    {
        drawSunWithGlow(1.2f, 0.7f, 0.10f);
    }
    else
    {

        // NIGHT SHADE
        glColor4f(0.0f, 0.0f, 0.2f, 0.6f);
        glBegin(GL_POLYGON);
        glVertex2f(-2,-2);
        glVertex2f( 2,-2);
        glVertex2f( 2, 2);
        glVertex2f(-2, 2);
        glEnd();

        // Moon
        drawCrescentMoon(-1.3f, 0.8f, 0.12f);
        drawStars();
    }

    //clouds
    drawCloud(-0.9f + cloudPosition, 0.65f);
    drawCloud(-0.3f + cloudPosition, 0.78f);
    drawCloud( 0.3f + cloudPosition, 0.78f);

    // FAIR OBJECTS
    drawMan(0.6f, -0.2f, 0.6f,   0.7f,0.5f,0.3f,  0.2f,0.5f,0.8f);
    drawMan(0.9f, -0.2f, 0.6f,   0.5f,0.3f,0.1f,  0.2f,0.7f,0.3f);
    drawMan(1.2f, -0.2f, 0.6f,   0.6f,0.4f,0.2f,  0.6f,1.0f,0.9f);
    drawMan(1.5f, -0.2f, 0.6f,   0.6f,0.4f,0.2f,  1.0f,1.0f,0.9f);

    drawStall(0.6f, -0.1f, " Mishtanno ");
    drawStall(0.9f, -0.1f, " Khelna Ghor");
    drawStall(1.2f, -0.1f, "  Pitha Ghar");
    drawStall(1.5f, -0.1f, "  Putul Bari");

    glutSwapBuffers();
}

     ///UPDATES
void update(int value)
{
    if(isPaused)
    {
        glutPostRedisplay();
        glutTimerFunc(16, update, 0);
        return;
    }

    cloudPosition += cloudSpeed;
    if(cloudPosition > 2.0f)
        cloudPosition = -2.0f;


    smallBoatX -= smallBoatSpeed;

    if (smallBoatScale < 0.6f)
{
    smallBoatScale += 0.001f;
}

    if (smallBoatX < -1.6f)
    {
        smallBoatX = 1.6f;
        smallBoatScale = 0.3f;
    }

    wheelAngle += 1.0f;
    waveTime += 0.05f;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}
           ///RESIZE_  PROPER SCALING
void reshape(GLsizei width, GLsizei height)
{
    if (height == 0)
        height = 1;

    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (width >= height)
        gluOrtho2D(-aspect, aspect, -1.0, 1.0);
    else
        gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);

    glMatrixMode(GL_MODELVIEW);
}
        ///MOUSE_BUTTON
void handleMouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN)
    {
        if (button == GLUT_LEFT_BUTTON)
        {
            cloudSpeed += 0.002f;
            smallBoatSpeed += 0.003f;
        }
        if (button == GLUT_RIGHT_BUTTON)
        {
            if (cloudSpeed > 0.002f)
                cloudSpeed -= 0.002f;
            if (smallBoatSpeed >0.003f)
                smallBoatSpeed -= 0.003f;

        }
    }
}
                 ///KEYBOARD
void handleKeypress(unsigned char key, int x, int y)
{
    if(key == 'd' || key == 'D')   // Day
        isDay = true;

    if(key == 'n' || key == 'N')   // Night
        isDay = false;

    if(key == 'a' || key == 'A')   // Pause all
        isPaused = true;

    if(key == 'w' || key == 'W')   // Resume all
        isPaused = false;

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(1200, 800);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("A Riverside Fair ");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, update, 0);
    glutMouseFunc(handleMouse);
    glutKeyboardFunc(handleKeypress);

    initGL();
    glutMainLoop();
    return 0;

}
