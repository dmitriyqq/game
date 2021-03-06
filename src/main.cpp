// #include <iostream>
// #include <thread>
// #include "Constants.hpp"
// #include "Camera.hpp"
// #include "VoxelSpace.hpp"
// #include "ISpaceGenerator.hpp"
// #include "KeyTable.hpp"
// #include "UI.hpp"
// #include "Game.hpp"
// #include <queue>

// class GameEnd : public IKeyboardSubscriber{
// public:
//     void processKey(char key) override {
//         if(key == 'q'){
//             throw std::logic_error("end fucking game");
//         }
//     }
// };

// class SnakeCamera{
//     NCursesRenderingBackend *__renderingBackend;
// public:
//     int width(){
//         return __renderingBackend->width();
//     }

//     int height(){
//         return __renderingBackend->height();
//     }

//     SnakeCamera(int width, int height) {
//         __renderingBackend = new NCursesRenderingBackend(width, height);
//     }

//     void display(const std::vector<IDrawable *> &drawables){
//         __renderingBackend->startDisplay();

//         for(auto &drawable: drawables){
//             drawable->draw(__renderingBackend);
//         }

//         __renderingBackend->endDisplay();
//     }
// };

// class Snake : public IKeyboardSubscriber, public IDrawable{
//     int __x = 1, __y = 1;
//     int __lenght = 3;
//     enum class Direction { NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3} __direction = Direction::EAST;

//     std::deque<std::pair<int, int> > __segments;

// public:
//     bool collide(int x, int y){
//         return (x == __x && y == __y);
//     }

//     void processKey(char key) override {
//         switch (key){
//             case 'w': __direction = Direction::NORTH; break;
//             case 'a': __direction = Direction::WEST; break;
//             case 's': __direction = Direction::SOUTH; break;
//             case 'd': __direction = Direction::EAST; break;
//             default: break;
//         }
//     }

//     void draw(IRenderingBackend * backend) const override{
//         Voxel voxel;
//         DebugWindow::debug("snakelength", (int)__segments.size());
//         voxel.type = Voxel::Type::SNOW;
//         for(auto &&s: __segments){
//             backend->display(voxel, s.second, s.first);
//         }
//     }

//     void move(){
//         using velocity = std::pair<int, int>;
//         std::array<velocity,4> VELOCITIES = {
//                 velocity(0, -1),
//                 velocity(1, 0),
//                 velocity(0, 1),
//                 velocity(-1, 0),
//         };

//         int dX = VELOCITIES[(int)__direction].first;
//         int dY = VELOCITIES[(int)__direction].second;
//         int newX = __x + dX;
//         int newY = __y + dY;

//         __segments.emplace_back(newX, newY);
//         __x = newX;
//         __y = newY;

//         DebugWindow::debug("snakex", __x);
//         DebugWindow::debug("snakey", __y);

//         if((int)__segments.size() > __lenght) {
//             __segments.pop_front();
//         }
//     }

//     void grow(){
//         this->__lenght++;
//     }
// };

// class SnakeBonus : public IDrawable{
// protected:
//     int __x = 0, __y = 0;

// public:
//     SnakeBonus(int x, int y): __x(x), __y(y){

//     }

//     virtual std::pair<bool, bool> isEaten(Snake &snake){
//         if(snake.collide(__x, __y)){
//             snake.grow();
//             return {true, false};
//         }else{
//             return {false, false};
//         }

//     }

//     void draw(IRenderingBackend * backend) const override{
//         Voxel voxel;
//         voxel.type = Voxel::Type::GRASS;
//         backend->display(voxel, __y, __x);
//         auto logger = spdlog::get(Constants::MAIN_LOGGER);
//         logger->error("draw a type{} at {} {}", (int)voxel.type,__x, __y);
//     }

//     void recreate(int newX, int newY){
//         auto logger = spdlog::get(Constants::MAIN_LOGGER);
//         logger->error("recreating at {} {}", newX, newY);
//         __x = newX;
//         __y = newY;
//     }
// };

// class Wall : public SnakeBonus{
// public:
//     Wall(int x, int y): SnakeBonus(x, y){};
//     std::pair<bool, bool> isEaten(Snake &snake) override{
//         if(snake.collide(__x, __y)){
//             return {true, true};
//         }else{
//             return {false, false};
//         }
//     }
//     void draw(IRenderingBackend * backend) const override{
//         Voxel voxel;
//         voxel.type = Voxel::Type::AIR;
//         backend->display(voxel, __y, __x);
//         auto logger = spdlog::get(Constants::MAIN_LOGGER);
//         logger->error("draw a type{} at {} {}", (int)voxel.type,__x, __y);
//     }
// };

// class CellsFactory{
//     std::map <std::pair<int, int>, SnakeBonus*> bonuses;
//     int __maxX;
//     int __maxY;
// public:
//     CellsFactory(int maxX, int maxY): __maxX(maxX), __maxY(maxY) {
//         for(int i = 0; i < 5; i++){
//             auto coords = getNewCellCords();
//             bonuses[coords] = new SnakeBonus(coords.first, coords.second);
//         }
//         for(int i = 0; i < 25; i++){
//             auto coords = getNewCellCords();
//             bonuses[coords] = new Wall(coords.first, coords.second);
//         }

//         for(int i = 0; i < __maxX; i++){
//             std::pair<int, int> coordsTop = {i, 0};
//             std::pair<int, int> coordsBot = {i, __maxY-1};
//             bonuses[coordsTop] = new Wall(coordsTop.first, coordsTop.second);
//             bonuses[coordsBot] = new Wall(coordsBot.first, coordsBot.second);
//         }

//         for(int i = 0; i < __maxY; i++){
//             std::pair<int, int> coordsTop = {0, i};
//             std::pair<int, int> coordsBot = {__maxX-1, i};
//             bonuses[coordsTop] = new Wall(coordsTop.first, coordsTop.second);
//             bonuses[coordsBot] = new Wall(coordsBot.first, coordsBot.second);
//         }
//     }


//     bool updateCells(Snake &snake){
//         for(auto &bonus: bonuses){
//             auto resp = bonus.second->isEaten(snake);
//             if(resp.second){
//                 return true;
//             }

//             if(resp.first){
//                 auto coords = getNewCellCords();
//                 bonus.second->recreate(coords.first, coords.second);
//             }
//         }

//         return false;
//     }

//     std::map<std::pair<int, int>, SnakeBonus* >& getCells(){
//         return bonuses;
//     }

//     std::pair<int, int> getNewCellCords(int seed = -1){
//         static std::mt19937 generator((unsigned int) time(nullptr));
//         auto logger = spdlog::get(Constants::MAIN_LOGGER);
//         logger->error("RND width height {} {}", __maxX, __maxY);
//         static std::uniform_int_distribution<int> distributionX(1, __maxX-1);
//         static std::uniform_int_distribution<int> distributionY(1, __maxY-1);
//         if(seed != -1) generator.seed(seed);
//         std::pair<int, int> coords(distributionX(generator), distributionY(generator));
//         while(bonuses.find(coords) != end(bonuses)){
//             coords.first = distributionX(generator);
//             coords.second = distributionY(generator);
//         }
//         return coords;
//     }
// };

// template <typename UiT>
// class Game : public IGame {
//     UiT __ui;
//     KeyTable keytable;
//     Snake __snake;
//     GameEnd __game_end;
//     CellsFactory *__factory;
//     std::vector <IDrawable*> drawables;

//     void update() override {
//         keytable.update();
//         __snake.move();
//         if(__factory->updateCells(__snake)){
//             __playing = false;
//         }
//     }

//     void draw() const override {
//         __ui.display(drawables);
//     }

// public:
//     Game(){
//         keytable.addSubscriber(&__snake);
//         keytable.addSubscriber(&__game_end);
//         drawables.push_back(&__snake);
//         __factory = new CellsFactory(__ui.gameWidth(), __ui.gameHeight());
//         auto c =__factory->getCells();
//         for(auto cell: c){
//             drawables.push_back(cell.second);
//         }
//     }
// };

// int main(){
//     auto logger = spdlog::basic_logger_mt(Constants::MAIN_LOGGER, "log.txt");
//     logger->error("Welcome to spdlog!");
//     logger->set_level(spdlog::level::info);
//     logger->flush_on(spdlog::level::debug);

//     try {
//         auto myGame = new Game<UI <SnakeCamera> >();
//         myGame->start();
//     }
//     catch (std::exception & e){
//         logger->error("exception_occured " + std::string(e.what()));
//         logger->error("shutdown" + std::string(e.what()));
//         logger->flush();

//         // TODO fix this
//         endwin();
//         return 23;
//     }

//     endwin();
//     return 0;
// }