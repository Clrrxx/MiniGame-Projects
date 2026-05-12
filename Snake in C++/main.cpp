#include <iostream>
#include <raylib.h>
#include <deque>
#include <raymath.h>

using namespace std;
Color green = {173, 204, 96, 255};
Color brown = {95, 70, 0, 255};
Color blue = {0, 0, 255, 255};
Color gold = {255, 215, 0, 255};
Color purple = {153, 102, 204, 255};


const int cellSize = 15;
const int cellCount = 50;
const int offset = 75;
double lastUpdateTime = 0;

bool eventTrig(double interval){
    double currTime = GetTime();
    if (currTime - lastUpdateTime >= interval){
        lastUpdateTime = currTime;
        return true;
    }
    return false;
}

bool inDeq(Vector2 element, const deque<Vector2> deq){
    for(unsigned int i = 0; i<deq.size(); i++){
        if (Vector2Equals(deq[i], element)){
            return true;
        }
    }
    return false;
}

class Food{
private:
    Vector2 GenerateRandomCell(){
        float x = GetRandomValue(0, cellCount-1);
        float y = GetRandomValue(0, cellCount-1);
        return Vector2{x, y};
    }
public:
    Vector2 pos; 
    Texture2D texture;

    Food(deque<Vector2> snake){
        Image image = LoadImage("W:/CODING STUFF/Programming Y1 sem2/Black-Jack/Snake in C++/Images/apple_pixel_15x15.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        pos = GenerateRandomPos(snake);
    }
       
    void Draw(){
        DrawTexture(texture, offset + pos.x*cellSize, offset + pos.y*cellSize, WHITE);
    }

    Vector2 GenerateRandomPos(const deque<Vector2> snake){
        Vector2 pos = GenerateRandomCell();
        while(inDeq(pos, snake)){
            pos = GenerateRandomCell();
        }
        return pos;
        
    }

    ~Food(){
        UnloadTexture(texture);
    }
};

class Snake{
public:
    deque<Vector2> body = {Vector2{6, 9}, Vector2{7, 9}, Vector2{8, 9}};
    Vector2 direction = {1, 0};
    bool addSeg = false;

    void Draw(){
        for (unsigned int i = 0; i<body.size(); i++){
            float x = body[i].x;
            float y = body[i].y;
            Rectangle rect = Rectangle{offset + x*cellSize, offset + y*cellSize, (float)cellSize, (float)cellSize};

            DrawRectangleRounded(rect, 0.5, 6, blue);
        }
    }

    void Update(){
        body.push_front(Vector2Add(body[0], direction));
        if (addSeg){
            addSeg = false;
        }else{
            body.pop_back();
        }
    }

    void Reset(){
        body = {Vector2{6, 9}, Vector2{7, 9}, Vector2{8, 9}};
        direction = {1, 0};
    }
};

class Game{
public:
    Snake* snake = new Snake();
    Food* fruit = new Food(snake->body);
    bool running = true;
    int score = 0;

    void Draw(){
        fruit->Draw();
        snake->Draw();
    }

    void Update(){
        
        if (running){
            snake->Update();
            eatFood();
            checkEdges();
            checkColl();
        }
    }

    void eatFood(){
        if (Vector2Equals(snake->body[0], fruit->pos)){
            fruit->pos = fruit->GenerateRandomPos(snake->body);
            snake->addSeg = true;
            score ++;
        }
    }

    void checkEdges(){
        if (snake->body[0].x == cellCount || snake->body[0].x == -1){
            GameOver();
        }
        if (snake->body[0].y == cellCount || snake->body[0].y == -1){
            GameOver();
        }
    }

    void checkColl(){
        deque<Vector2> snakebody = snake->body;
        snakebody.pop_front();
        if (inDeq(snake->body[0], snakebody)){
            GameOver();
        }
    }

    void GameOver(){
        snake->Reset();
        fruit->pos = fruit->GenerateRandomPos(snake->body);
        running = false;
        score = 0;
    }
    ~Game(){
        delete snake;
        delete fruit;
    }
};

int main () {
    cout << "Starting the Game..." << endl;
    InitWindow(2 * offset + cellSize*cellCount,2 * offset + cellSize*cellCount, "Snake with RayLib");
    SetTargetFPS(60);

    Game* gameSess = new Game();
    while (WindowShouldClose() == false){
        BeginDrawing();
        
        if (eventTrig(0.2)){
            gameSess->Update();
        }

        if (IsKeyPressed(KEY_UP) && gameSess->snake->direction.y != 1){gameSess->snake->direction = {0, -1}; gameSess->running = true;}
        if (IsKeyPressed(KEY_LEFT) && gameSess->snake->direction.x != 1){gameSess->snake->direction = {-1, 0}; gameSess->running = true;}
        if (IsKeyPressed(KEY_DOWN) && gameSess->snake->direction.y != -1){gameSess->snake->direction = {0, 1}; gameSess->running = true;}
        if (IsKeyPressed(KEY_RIGHT) && gameSess->snake->direction.x != -1){gameSess->snake->direction = {1, 0}; gameSess->running = true;}


        ClearBackground(green);
        DrawRectangleLinesEx(Rectangle{(float)offset - 5, (float)offset-5, (float)cellSize*cellCount+10, (float)cellSize*cellCount+10}, 10, brown);
        DrawText("Snake in C++", offset - 5, 20, 40, gold);
        DrawText(TextFormat("Score: %i", gameSess->score), 650, 20, 40, purple);
        gameSess->Draw();

        EndDrawing();
    }
    
    delete gameSess;
    CloseWindow();
    return 0;
}