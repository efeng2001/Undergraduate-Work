#include <vector>
#include <stdexcept>

#include "reversi.h"

using namespace std;




void Square::flip()
{
    switch (value_)
    {
    case WHITE:
        value_ = BLACK;
        break;
    case BLACK:
        value_ = WHITE;
        break;
    default:
        break;
    }
}

Square::SquareValue opposite_color(Square::SquareValue value)
{
    switch (value)
    {
    case Square::WHITE:
        return Square::BLACK;
    case Square::BLACK:
        return Square::WHITE;
    default:
        throw invalid_argument("Illegal square value");
    }
}

Square& Square::operator=(SquareValue value)
{
    value_ = value;
    return *this;
}

bool Square::operator==(SquareValue value) const
{
    return (value_==value);
}

bool Square::operator!=(SquareValue value) const
{
    return (value_!=value);
}   




std::ostream& operator<<(std::ostream& out, const Square& square)
{
    if(square.value_ == Square::FREE){
        out << "-";
    }else if(square.value_ == Square::WHITE){
        out << "W";
    }else if(square.value_ == Square::BLACK){
        out << "B";
    }
    return out; 
}


Board::Board(size_t s)
{
    dimension_ = s;
    squares_ = new Square*[s];
    for(size_t i=0; i<s; i++)
    {
        squares_[i] = new Square[s];
    }
}

Board::Board(const Board &board)
{
    dimension_ = board.dimension_;
    squares_ = new Square*[dimension_];
    for(size_t i=0; i<dimension_; i++)
    {
        squares_[i] = new Square[dimension_];
    }
    for(size_t i=0; i<dimension_;i++){
        for(size_t j=0; j<dimension_;j++){
            squares_[i][j] = board.squares_[i][j];
        }
    }
}

Board& Board::operator=(const Board &board)
{
    dimension_ = board.dimension_;
    if(squares_){
        for(size_t i=0; i<dimension_; i++)
        {
            delete[] squares_[i];
        }
        delete[] squares_;
    }
    squares_ = new Square*[dimension_];
    for(size_t i=0; i<dimension_; i++)
    {
        squares_[i] = new Square[dimension_];
    }
    for(size_t i=0; i<dimension_;i++){
        for(size_t j=0; j<dimension_;j++){
            squares_[i][j] = board.squares_[i][j];
        }
    }
    return (*this);
}

Board::~Board()
{
    for(size_t i=0; i<dimension_; i++)
    {
        delete[] squares_[i];
    }
    delete[] squares_;
}


Square& Board::operator()(char row, size_t column)
{
    if (!is_valid_location(row, column))
    {
        throw out_of_range("Bad row index");
    }
    size_t row_index = row_to_index(row);
    return squares_[row_index][column - 1];
}

Square const& Board::operator()(char row, size_t column) const
{
    if (!is_valid_location(row, column))
    {
        throw out_of_range("Bad row index");
    }
    size_t row_index = row_to_index(row);
    return squares_[row_index][column - 1];
}

bool Board::is_legal_and_opposite_color(
    char row, size_t column, Square::SquareValue turn) const
{
    if (is_valid_location(row, column))
    {
        size_t row_index = row_to_index(row);
        return squares_[row_index][column - 1] != Square::FREE && squares_[row_index][column - 1] != turn;
    }
    return false;
}

bool Board::is_legal_and_same_color(
    char row, size_t column, Square::SquareValue turn) const
{
    if (is_valid_location(row, column))
    {
        size_t row_index = row_to_index(row);
        return squares_[row_index][column - 1] == turn;
    }
    return false;
}

bool Board::is_valid_location(char row, size_t column) const
{
    size_t row_index = row_to_index(row);
    return row_index < dimension_ && column - 1 < dimension_;
}

std::ostream& operator<<(std::ostream& out, const Board& board)
{
    return board.print(out);
}


Checkpoint::Checkpoint(const Board& b, Square::SquareValue turn) :
    board_(b), turn_(turn)
{

}

ostream& Board::print(ostream& out) const
{
    out << "  ";
    for (size_t i = 1; i <= dimension_; i++)
    {
        if (i < 10)
        {
            out << " ";
        }
        else
        {
            out << (i / 10);
        }
    }
    out << endl;
    out << "  ";
    for (size_t i = 1; i <= dimension_; i++)
    {
        out << (i % 10);
    }
    out << endl;
    for (size_t i = 0; i < dimension_; i++)
    {
        out << (char)('a' + i) << ':';
        for (size_t k = 0; k < dimension_; k++)
        {
            out << squares_[i][k];
        }
        out << endl;
    }
    return out;
}

Reversi::Reversi(size_t size)
: board_(size), turn_(Square::BLACK)
{
    for(size_t i=0; i<size; i++){
        for(size_t j=1; j<=size; j++){
            if(i==size/2-1 && j==size/2){
                board_((char)('a' + i),j) = Square::BLACK;
            }else if(i==size/2-1 && j==size/2+1){
                board_((char)('a' + i),j) = Square::WHITE;
            }else if(i==size/2 && j==size/2){
                board_((char)('a' + i),j) = Square::WHITE;
            }else if(i==size/2 && j==size/2+1){
                board_((char)('a' + i),j) = Square::BLACK;
            }else{
                board_((char)('a' + i),j) = Square::FREE;
            }
        }
    }
}

Reversi::~Reversi()
{
    while(history_.size() != 0){
        history_.pop_back();
    }
}

void Reversi::prompt() const
{
    cout << board_ << endl;
    cout << (turn_ == Square::BLACK ? "B" : "W");
    cout << " - Enter 'p r/c', 'q', 'c', 'u':" << endl;
}

void Reversi::win_loss_tie_message(size_t white_count, size_t black_count)
{
    cout << board_ << endl;
    if (white_count > black_count)
    {
        cout << "W wins" << endl;
    }
    else if (white_count < black_count)
    {
        cout << "B wins" << endl;
    }
    else
    {
        cout << "Tie" << endl;
    }
    cout << "W=" << white_count << "/B=" << black_count << endl;
}

bool Reversi::is_legal_choice(char row, size_t column, Square::SquareValue turn) const
{
    // Vectors for each cardinal direction
    const size_t direction_count = 8;
    const int direction_row[] =    {-1, -1,  0, +1, +1, +1,  0, -1};
    const int direction_column[] = { 0, -1, -1, -1,  0, +1, +1, +1};

    // Make sure location is free
    if (board_(row, column) != Square::FREE)
    {
        return false;
    }

    // Now check in each directions
    for (size_t d = 0; d < direction_count; d++)
    {
        // Where we're checking
        char cursor_row = row + direction_row[d];
        size_t cursor_column = column + direction_column[d];

        // Move towards the direction while we're on the opposite color
        bool found_opposite = false;
        while (board_.is_legal_and_opposite_color(cursor_row, cursor_column, turn_))
        {
            found_opposite = true;
            cursor_row += direction_row[d];
            cursor_column += direction_column[d];
        }

        // Check if the next thing after is our color
        bool found_same = board_.is_legal_and_same_color(cursor_row, cursor_column, turn_);

        // If this direction is valid, the move is valid, so short circuit and return
        if (found_opposite && found_same) {
            return true;
        }
    }
    return false;
}

bool Reversi::is_game_over() const
{
    for (unsigned char row = 'a'; row < 'a' + board_.dimension(); row++)
    {
        for (size_t column = 1; column <= board_.dimension(); column++)
        {
            if (is_legal_choice(row, column, turn_))
            {
                return false;
            }
        }
    }
    return true;
}

void Reversi::save_checkpoint()
{
    history_.push_back(Checkpoint(board_, turn_));
}

void Reversi::undo()
{
    if(history_.size()==0){
        return;
    }else{
        board_ = history_.back().board_;
        turn_ = history_.back().turn_;
        history_.pop_back();
    }
}

void Reversi::play()
{
    char x, r;
    size_t c, white=0, black=0;

    const size_t direction_count = 8;
    const int direction_row[] =    {-1, -1,  0, +1, +1, +1,  0, -1};
    const int direction_column[] = { 0, -1, -1, -1,  0, +1, +1, +1};



    while(!is_game_over()){
        prompt();
        cin >> x;

        if(x == 'p'){
            cin >> r >> c; 
            board_(r,c);
            if(is_legal_choice(r, c, turn_)){
                board_(r, c) = turn_;
                for (size_t d = 0; d < direction_count; d++)
                {
                    // Where we're checking
                    char cursor_row = r + direction_row[d];
                    size_t cursor_column = c + direction_column[d];

                    // Move towards the direction while we're on the opposite color
                    bool found_opposite = false;
                    while (board_.is_legal_and_opposite_color(cursor_row, cursor_column, turn_))
                    {
                        found_opposite = true;
                        cursor_row += direction_row[d];
                        cursor_column += direction_column[d];
                    }

                    // Check if the next thing after is our color
                    bool found_same = board_.is_legal_and_same_color(cursor_row, cursor_column, turn_);

                    // If this direction is valid, the move is valid, so flip everything in between
                    if (found_opposite && found_same) {
                        cursor_row -= direction_row[d]; 
                        cursor_column -= direction_column[d];
                        while (cursor_row != r || cursor_column != c)
                        {
                            board_(cursor_row, cursor_column).flip();
                            cursor_row -= direction_row[d];
                            cursor_column -= direction_column[d];
                        }
                    }
                }
                turn_ = opposite_color(turn_);
            }
        }else if(x == 'c'){
            save_checkpoint();
        }else if(x == 'u'){
            undo();
        }else if(x == 'q'){
            break;
        }
    }
    for(size_t i=0; i<board_.dimension(); i++){
        for(size_t j=1; j<=board_.dimension(); j++){
            if(board_((char)('a' + i),j) == Square::WHITE){
                white++;
            }else if(board_((char)('a' + i),j) == Square::BLACK){
                black++;
            }
        }
    }
    win_loss_tie_message(white, black); 
}


