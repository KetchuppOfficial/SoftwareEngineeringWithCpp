#include <memory>
#include <print>
#include <string>
#include <string_view>
#include <vector>

class GameObject {
  public:
    virtual ~GameObject() = default;

    virtual void update() = 0;
    virtual void render() const = 0;
};

// Composite
class GameObjectGroup final : public GameObject {
  public:
    ~GameObjectGroup() override = default;

    void add(std::unique_ptr<GameObject> obj) { children.push_back(std::move(obj)); }

    void update() override {
        for (auto &obj : children) {
            obj->update();
        }
    }

    void render() const override {
        for (const auto &obj : children) {
            obj->render();
        }
    }

  private:
    std::vector<std::unique_ptr<GameObject>> children;
};

class AttackStrategy {
  public:
    virtual ~AttackStrategy() = default;
    virtual int attack() const = 0;
};

class SpellCast final : public AttackStrategy {
  public:
    int attack() const override {
        std::println("Spell cast");
        return 40;
    }
};

class SwordAttack final : public AttackStrategy {
  public:
    int attack() const override {
        std::println("Sword attack");
        return 20;
    }
};

class Unit : public GameObject {
  public:
    Unit(std::string_view name, int health) : name_{name}, health_{health} {}
    ~Unit() override = default;

    void set_attack_strategy(std::unique_ptr<AttackStrategy> strategy) {
        attack_strategy_ = std::move(strategy);
    }

    // Template Method
    void update() override final {
        move();
        attack_enemy();
    }

    void render() const override { std::println("Unit: {}, HP: {}", name_, health_); }

  protected:
    std::string name_;
    int health_;
    std::unique_ptr<AttackStrategy> attack_strategy_;

    virtual void move() = 0;

    void attack_enemy() {
        if (attack_strategy_) {
            health_ -= attack_strategy_->attack();
        }
    }
};

using namespace std::string_view_literals;

class Sorcerer final : public Unit {
  public:
    Sorcerer() : Unit{"Sorcerer"sv, 70} {}
    ~Sorcerer() override = default;

  protected:
    void move() override { std::println("Sorcerer moves"); }
};

class Knight final : public Unit {
  public:
    Knight() : Unit{"Knight"sv, 100} {}
    ~Knight() override = default;

  protected:
    void move() override { std::println("Knight moves"); }
};

class UnitBuilder {
  public:
    virtual ~UnitBuilder() = default;

    virtual void buildUnit() = 0;
    virtual void buildAttack() = 0;
    virtual std::unique_ptr<Unit> getResult() && = 0;
};

class SorcererBuilder final : public UnitBuilder {
  public:
    ~SorcererBuilder() override = default;

    void buildUnit() override { sorcerer_ = std::make_unique<Sorcerer>(); }
    void buildAttack() override { sorcerer_->set_attack_strategy(std::make_unique<SpellCast>()); }

    std::unique_ptr<Unit> getResult() && override { return std::move(sorcerer_); }

  private:
    std::unique_ptr<Sorcerer> sorcerer_;
};

class KnightBuilder final : public UnitBuilder {
  public:
    ~KnightBuilder() override = default;

    void buildUnit() override { knight_ = std::make_unique<Knight>(); }
    void buildAttack() override { knight_->set_attack_strategy(std::make_unique<SwordAttack>()); }

    std::unique_ptr<Unit> getResult() && override { return std::move(knight_); }

  private:
    std::unique_ptr<Knight> knight_;
};

class UnitDirector {
  public:
    std::unique_ptr<Unit> createUnit(UnitBuilder &&builder) {
        builder.buildUnit();
        builder.buildAttack();
        return std::move(builder).getResult();
    }
};

int main() {
    UnitDirector director;

    auto squad = std::make_unique<GameObjectGroup>();
    squad->add(director.createUnit(SorcererBuilder{}));
    squad->add(director.createUnit(KnightBuilder{}));

    std::println("=== Game Render ===");
    squad->render();

    std::println("\n=== Game Update ===");
    squad->update();

    std::println("\n=== Game Render ===");
    squad->render();

    return 0;
}
