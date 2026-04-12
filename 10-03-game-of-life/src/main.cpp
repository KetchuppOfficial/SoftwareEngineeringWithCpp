#include <algorithm>
#include <array>
#include <chrono>
#include <functional>
#include <iostream>
#include <random>
#include <ranges>
#include <thread>

#include <boost/multi_array.hpp>

namespace {

using namespace std::chrono_literals;

class GameOfLife {
  public:
    GameOfLife(std::size_t rows, std::size_t cols) : grid(boost::extents[rows][cols]), dist(0, 4) {
        std::random_device rd;
        std::array<int, std::mt19937::state_size> seed_data{};
        std::ranges::generate(seed_data, std::ref(rd));
        std::seed_seq seq(seed_data.begin(), seed_data.end());
        mt.seed(seq);
    }

    void run(std::size_t generations, std::chrono::milliseconds sleep_time = 100ms) {
        initialize();
        display();
        for (auto _ : std::views::iota(0uz, generations)) {
            next_generation();
            display();
            std::this_thread::sleep_for(sleep_time);
        }
    }

  private:
    void next_generation() {
        const auto rows = this->rows();
        const auto cols = this->cols();
        decltype(grid) new_grid{boost::extents[rows][cols]};
        for (std::size_t r : std::views::iota(0uz, rows)) {
            for (std::size_t c : std::views::iota(0uz, cols)) {
                new_grid[r][c] = [cell = static_cast<unsigned char>(grid[r][c]),
                                  count = count_neighbors(r, c)] {
                    if (cell == kAlive) {
                        return (count == 2 || count == 3) ? kAlive : kDead;
                    } else {
                        return (count == 3) ? kAlive : kDead;
                    }
                }();
            }
        }
        grid = std::move(new_grid);
    }

    void display() const {
        for (std::size_t r : std::views::iota(0uz, rows())) {
            for (std::size_t c : std::views::iota(0uz, cols())) {
                std::cout << (grid[r][c] ? '*' : ' ');
            }
            std::cout << std::endl;
        }
    }

    void initialize() {
        for (std::size_t r : std::views::iota(0uz, rows())) {
            for (std::size_t c : std::views::iota(0uz, cols())) {
                grid[r][c] = (dist(mt) == 0) ? kAlive : kDead;
            }
        }
    }

    template <typename... T>
    static auto count_alive(T... ts) {
        return (ts + ...);
    }

    int count_neighbors(std::size_t row, std::size_t col) const {
        const auto rows = this->rows();
        const auto cols = this->cols();

        if (row == 0) {
            if (col == 0) {
                return count_alive(grid[0][1], grid[1][1], grid[1][0]);
            } else if (col == cols - 1) {
                return count_alive(grid[0][cols - 2], grid[1][cols - 2], grid[1][cols - 1]);
            } else {
                return count_alive(grid[0][col - 1], grid[1][col - 1], grid[1][col],
                                   grid[1][col + 1], grid[0][col + 1]);
            }
        } else if (row == rows - 1) {
            if (col == 0) {
                return count_alive(grid[rows - 2][0], grid[rows - 2][1], grid[rows - 1][1]);
            } else if (col == cols - 1) {
                return count_alive(grid[rows - 2][cols - 1], grid[rows - 2][cols - 2],
                                   grid[rows - 1][cols - 2]);
            } else {
                return count_alive(grid[row][col - 1], grid[row - 1][col - 1], grid[row - 1][col],
                                   grid[row - 1][col + 1], grid[row][col + 1]);
            }
        } else {
            if (col == 0) {
                return count_alive(grid[row - 1][0], grid[row - 1][1], grid[row][1],
                                   grid[row + 1][1], grid[row + 1][0]);
            } else if (col == cols - 1) {
                return count_alive(grid[row - 1][col], grid[row - 1][col - 1], grid[row][col - 1],
                                   grid[row + 1][col - 1], grid[row + 1][col]);
            } else {
                return count_alive(grid[row - 1][col - 1], grid[row - 1][col],
                                   grid[row - 1][col + 1], grid[row][col + 1],
                                   grid[row + 1][col + 1], grid[row + 1][col],
                                   grid[row + 1][col - 1], grid[row][col - 1]);
            }
        }
    }

    std::size_t rows() const { return grid.shape()[0]; }
    std::size_t cols() const { return grid.shape()[1]; }

    static constexpr unsigned char kDead = 0;
    static constexpr unsigned char kAlive = 1;

    boost::multi_array<unsigned char, 2> grid;
    std::uniform_int_distribution<> dist;
    std::mt19937 mt;
};

} // unnamed namespace

int main() {
    constexpr std::size_t kGridSize = 10;
    constexpr std::size_t kGenerations = 100;

    GameOfLife u(kGridSize, kGridSize + 1);
    u.run(kGenerations);
}
