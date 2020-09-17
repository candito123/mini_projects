#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
using namespace std;

const int MAXROWS = 20;
const int MAXCOLS = 40;
const int MAXSPIDERS = 170;

const int UP    = 0;
const int DOWN  = 1;
const int LEFT  = 2;
const int RIGHT = 3;
const int NUMDIRS = 4;

class Pit;

class Spider
{
public:
    Spider(Pit* pp, int r, int c);

    int  row() const;
    int  col() const;
    void move();

private:
    Pit* m_pit;
    int  m_row;
    int  m_col;
};

class Player
{
public:
    Player(Pit *pp, int r, int c);

    int  row() const;
    int  col() const;
    int  age() const;
    bool isDead() const;

    void   stand();
    void   move(int dir);
    void   setDead();

private:
    Pit*  m_pit;
    int   m_row;
    int   m_col;
    int   m_age;
    bool  m_dead;
};

class Pit
{
public:
    Pit(int nRows, int nCols);
    ~Pit();

    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     spiderCount() const;
    int     numberOfSpidersAt(int r, int c) const;
    void    display() const;

    bool   addSpider(int r, int c);
    bool   addPlayer(int r, int c);
    bool   destroyOneSpider(int r, int c);
    bool   moveSpiders();

private:
    int      m_rows;
    int      m_cols;
    Player*  m_player;
    Spider*  m_spiders[MAXSPIDERS]={};
    int      m_nSpiders;

    bool isPosInBounds(int r, int c) const;
};

class Game
{
public:
    Game(int rows, int cols, int nSpiders);
    ~Game();

    void play();

private:
    Pit* m_pit;

};

int randInt(int min, int max);
int decodeDirection(char dir);
bool directionToDeltas(int dir, int& rowDelta, int& colDelta);
void clearScreen();

Spider::Spider(Pit* pp, int r, int c)
{
    if (pp == nullptr)
    {
        cout << "***** A spider must be created in some Pit!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > pp->rows()  ||  c < 1  ||  c > pp->cols())
    {
        cout << "***** Spider created with invalid coordinates (" << r << ","
        << c << ")!" << endl;
        exit(1);
    }
    m_pit = pp;
    m_row = r;
    m_col = c;
}

int Spider::row() const
{
    return m_row;
}

int Spider::col() const
{
    return Spider::m_col;
}

void Spider::move()
{
    switch (randInt(0, NUMDIRS-1))
    {
        case UP:
            if(m_pit!=nullptr && Spider::m_row-1 >= 1)
                Spider::m_row--;
            break;
        case DOWN:
            if(m_pit!=nullptr && Spider::m_row+1<=m_pit->Pit::rows())
                Spider::m_row++;
            break;
        case LEFT:
            if(m_pit!=nullptr && Spider::m_col-1>= 1)
                Spider::m_col--;
            break;
        case RIGHT:
            if(m_pit!=nullptr && Spider::m_col+1<=m_pit->Pit::cols())
                Spider::m_col++;
            break;
    }
}


Player::Player(Pit* pp, int r, int c)
{
    if (pp == nullptr)
    {
        cout << "***** The player must be created in some Pit!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > pp->rows()  ||  c < 1  ||  c > pp->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
        << "," << c << ")!" << endl;
        exit(1);
    }
    m_pit = pp;
    m_row = r;
    m_col = c;
    m_age = 0;
    m_dead = false;
}

int Player::row() const
{
    return m_row;
}

int Player::col() const
{
    return m_col;
}

int Player::age() const
{
    return m_age;
}

void Player::stand()
{
    m_age++;
}

void Player::move(int dir)
{
    m_age++;

    bool jj=false;
    bool jjsp=false;
    bool j=false;
    bool jsp=false;

    switch (dir)
    {
        case UP:
            if(Player::row()-2 >= 1)
                jj=true;
            if (m_row-1 >= 1)
                j=true;
            if(m_pit->Pit::numberOfSpidersAt(Player::row()-2,Player::col())!=0)
               jjsp=true;
            if(m_pit->Pit::numberOfSpidersAt(Player::row()-1,Player::col())!=0)
                jsp=true;
            break;
        case DOWN:
            if(Player::row()+2<=m_pit->Pit::rows())
                jj=true;
            if(Player::row()+1<=m_pit->Pit::rows())
                j=true;
            if(m_pit->Pit::numberOfSpidersAt(Player::row()+2,Player::col())!=0)
                jjsp=true;
            if(m_pit->Pit::numberOfSpidersAt(Player::row()+1,Player::col())!=0)
                jsp=true;
            break;
        case LEFT:
            if(Player::col()-2>= 1)
                jj=true;
            if(Player::col()-1>= 1)
                j=true;
            if(m_pit->Pit::numberOfSpidersAt(Player::row(),Player::col()-2)!=0)
                jjsp=true;
            if(m_pit->Pit::numberOfSpidersAt(Player::row(),Player::col()-1)!=0)
                jsp=true;
            break;
        case RIGHT:
            if(Player::col()+2<=m_pit->Pit::cols())
                jj=true;
            if (Player::col()+1<=m_pit->Pit::cols())
                j=true;
            if(m_pit->Pit::numberOfSpidersAt(Player::row(),Player::col()+2)!=0)
                jjsp=true;
            if(m_pit->Pit::numberOfSpidersAt(Player::row(),Player::col()+1)!=0)
                jsp=true;
            break;
    }

    if(j && !jj && jsp )
    {
        switch(dir)
        {
            case UP:
                m_pit->destroyOneSpider(Player::row()-1,Player::col());
                    Player::m_row-=1;
                if(m_pit->Pit::numberOfSpidersAt(Player::row()-1,Player::col())!=0)
                {
                    setDead();
                }
                break;

            case DOWN:
                m_pit->destroyOneSpider(Player::row()+1,Player::col());
                Player::m_row+=1;
                if(m_pit->Pit::numberOfSpidersAt(Player::row()+1,Player::col())!=0)
                {
                    setDead();
                }
                break;

            case LEFT:
                 m_pit->destroyOneSpider(Player::row(),Player::col()-1);
                Player::m_col-=1;
                if(m_pit->Pit::numberOfSpidersAt(Player::row(),Player::col()-1)!=0)
                {
                    setDead();
                }
                break;

            case RIGHT:
                 m_pit->destroyOneSpider(Player::row(),Player::col()+1);
                Player::m_col+=1;
                if(m_pit->Pit::numberOfSpidersAt(Player::row(),Player::col()+1)!=0)
                {
                    setDead();
                }
                break;
        }
    }
    else if(jj && jsp)
    {
        switch(dir)
        {
            case UP:
                m_pit->destroyOneSpider(Player::row()-1,Player::col());
                Player::m_row-=2;
                break;

            case DOWN:
                m_pit->destroyOneSpider(Player::row()+1,Player::col());
                Player::m_row+=2;
                break;

            case LEFT:
                m_pit->destroyOneSpider(Player::row(),Player::col()-1);
                Player::m_col-=2;
                break;

            case RIGHT:
                m_pit->destroyOneSpider(Player::row(),Player::col()+1);
                Player::m_col+=2;
                break;
        }
        if(jjsp)
        {
            setDead();
        }
    }
    else if(j & !jsp)
    {
        switch(dir)
        {
            case UP:
                Player::m_row-=1;
                break;

            case DOWN:
                Player::m_row+=1;
                break;

            case LEFT:
                Player::m_col-=1;
                break;

            case RIGHT:
                Player::m_col+=1;
                break;
        }
    }
}
bool Player::isDead() const
{
    return m_dead;
}
void Player::setDead()
{
    m_dead = true;
}
Pit::Pit(int nRows, int nCols)
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** Pit created with invalid size " << nRows << " by "
        << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nSpiders = 0;
}
Pit::~Pit()
{
    delete m_player;
    m_player=nullptr;
    for (int i=0; i<MAXSPIDERS; i++)
    {
        delete m_spiders[i];
        if(m_spiders[i]!=nullptr)
        {
           m_spiders[i]=nullptr;
        }
    }
}
int Pit::rows() const
{
    return m_rows;
}
int Pit::cols() const
{
    return m_cols;
}
Player* Pit::player() const
{
    return m_player;
}
int Pit::spiderCount() const
{
    return m_nSpiders;
}
int Pit::numberOfSpidersAt(int r, int c) const
{
    int cnt=0;

    for(int i=0; i<MAXSPIDERS;i++)
    {
        if(m_spiders[i]!=nullptr &&
           m_spiders[i]->Spider::row()==r && m_spiders[i]->Spider::col()==c)
        {
            cnt++;
        }
    }
    return cnt;
}
void Pit::display() const
{
    char grid[MAXROWS][MAXCOLS];
    int r, c;

    for (r = 0; r < rows(); r++)
        for (c = 0; c < cols(); c++)
            grid[r][c] = '.';

    for (r = 0; r < rows(); r++)
        for (c = 0; c < cols(); c++)
            if(numberOfSpidersAt(r+1, c+1)!=0 &&
               numberOfSpidersAt(r+1, c+1)!=1 &&
               numberOfSpidersAt(r+1, c+1)>9)
                grid[r][c]= '9';
            else if (numberOfSpidersAt(r+1, c+1)!=0 &&
                     numberOfSpidersAt(r+1, c+1)!=1)
                grid[r][c] = char('0'+numberOfSpidersAt(r+1, c+1));
            else if(numberOfSpidersAt(r+1, c+1)==1)
                grid[r][c] = 'S';

    if (m_player != nullptr)
    {
        char& gridChar = grid[m_player->row()-1][m_player->col()-1];
        if (m_player->isDead())
            gridChar = '*';
        else
            gridChar = '@';
    }

    clearScreen();
    for (r = 0; r < rows(); r++)
    {
        for (c = 0; c < cols(); c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;

    cout << "There are " << spiderCount() << " spiders remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player." << endl;
    else
    {
        if (m_player->age() > 0)
            cout << "The player has lasted " << m_player->age() << " steps." << endl;
        if (m_player->isDead())
            cout << "The player is dead." << endl;
    }
}
bool Pit::addSpider(int r, int c)
{
    if (! isPosInBounds(r, c))
        return false;

    if (m_player != nullptr  &&  m_player->row() == r  &&  m_player->col() == c)
        return false;

    if (spiderCount()==MAXSPIDERS)
        return false;

    this->m_spiders[m_nSpiders]= new Spider(this, r, c);
    m_nSpiders++;

    return true;
}
bool Pit::addPlayer(int r, int c)
{
    if (! isPosInBounds(r, c))
        return false;

    if (m_player != nullptr)
        return false;

    if (numberOfSpidersAt(r, c) > 0)
        return false;

    m_player = new Player(this, r, c);
    return true;
}
bool Pit::destroyOneSpider(int r, int c)
{
    for(int i=0; i<MAXSPIDERS;i++)
    {
        if(m_spiders[i]!=nullptr &&
           m_spiders[i]->Spider::row()==r &&
           m_spiders[i]->Spider::col()==c)
        {
            delete m_spiders[i];
            m_spiders[i]=nullptr;
            m_nSpiders--;
            return true;
        }
    }
    return false;
}
bool Pit::moveSpiders()
{
    for (int k = 0; k < MAXSPIDERS; k++)
    {

        if(m_spiders[k]!=nullptr)
            m_spiders[k]->move();
        if(m_spiders[k]!=nullptr&&m_spiders[k]->Spider::row()== m_player->Player::row() && m_spiders[k]->Spider::col()==m_player->Player::col())
        {
            m_player->Player::setDead();
        }
    }
    return ! m_player->isDead();
}
bool Pit::isPosInBounds(int r, int c) const
{
    return (r >= 1  &&  r <= m_rows  &&  c >= 1  &&  c <= m_cols);
}
Game::Game(int rows, int cols, int nSpiders)
{
    if (nSpiders < 0)
    {
        cout << "***** Cannot create Game with negative number of spiders!" << endl;
        exit(1);
    }
    if (nSpiders > MAXSPIDERS)
    {
        cout << "***** Trying to create Game with " << nSpiders
        << " spiders; only " << MAXSPIDERS << " are allowed!" << endl;
        exit(1);
    }
    if (rows == 1  &&  cols == 1  &&  nSpiders > 0)
    {
        cout << "***** Cannot create Game with nowhere to place the spiders!" << endl;
        exit(1);
    }
    m_pit = new Pit(rows, cols);

    int rPlayer = randInt(1, rows);
    int cPlayer = randInt(1, cols);
    m_pit->addPlayer(rPlayer, cPlayer);

    while (nSpiders > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        if (r == rPlayer  &&  c == cPlayer)
            continue;
        m_pit->addSpider(r, c);
        nSpiders--;
    }
}
Game::~Game()
{
    delete m_pit;
}
void Game::play()
{
    m_pit->display();
    Player* player = m_pit->player();
    if (player == nullptr)
        return;

    while ( ! m_pit->player()->isDead()  &&  m_pit->spiderCount() > 0)
    {
        cout << "Move (u/d/l/r//q): ";
        string action;
        getline(cin,action);
        if (action.size() == 0)
            player->stand();
        else
        {
            switch (action[0])
            {
                default:
                    cout << '\a' << endl;
                    continue;
                case 'q':
                    return;
                case 'u':
                case 'd':
                case 'l':
                case 'r':
                    player->move(decodeDirection(action[0]));
                    break;
            }
        }
        if ( ! player->isDead())
            m_pit->moveSpiders();
        m_pit->display();
    }
    if (m_pit->player()->isDead())
        cout << "You lose." << endl;
    else
        cout << "You win." << endl;
}
int randInt(int min, int max)
{
    if (max < min)
        swap(max, min);
    static random_device rd;
    static default_random_engine generator(rd());
    uniform_int_distribution<> distro(min, max);
    return distro(generator);
}
int decodeDirection(char dir)
{
    switch (dir)
    {
        case 'u':  return UP;
        case 'd':  return DOWN;
        case 'l':  return LEFT;
        case 'r':  return RIGHT;
    }
    return -1;
}
bool directionToDeltas(int dir, int& rowDelta, int& colDelta)
{
    switch (dir)
    {
        case UP:     rowDelta = -1; colDelta =  0; break;
        case DOWN:   rowDelta =  1; colDelta =  0; break;
        case LEFT:   rowDelta =  0; colDelta = -1; break;
        case RIGHT:  rowDelta =  0; colDelta =  1; break;
        default:     return false;
    }
    return true;
}
int main()
{
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 3, 2);
    Game g(3, 3, 2);
    g.play();
}
#ifdef _MSC_VER  //  Microsoft Visual C++

#pragma warning(disable : 4005)
#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                               &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}
#else  // not Microsoft Visual C++, so assume UNIX interface

#include <iostream>
#include <cstring>
#include <cstdlib>

void clearScreen()  // will just write a newline in an Xcode output window
{
    static const char* term = getenv("TERM");
    if (term == nullptr  ||  strcmp(term, "dumb") == 0)
        cout << endl;
    else
    {
        static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
    }
}
#endif
