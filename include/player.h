#pragma once

#include "bn_camera_ptr.h"
#include "bn_core.h"
#include "bn_fixed.h"
#include "bn_fixed_point.h"
#include "bn_format.h"
#include "bn_log.h"
#include "bn_math.h"
#include "bn_memory.h"
#include "bn_optional.h"
#include "bn_regular_bg_item.h"
#include "bn_regular_bg_ptr.h"
#include "bn_rumble_actions.h"
#include "bn_size.h"
#include "bn_sprite_builder.h"
#include "bn_sprite_items_bear.h"
#include "bn_sprite_ptr.h"
#include "bn_timer.h"
#include "bn_unique_ptr.h"
#include "bn_vector.h"
#include "cursor.h"
#include "debug.h"
#include "level.h"

namespace cd
{
    class Game;
    class Player
    {
    public:
        Player(bn::camera_ptr _camera);
        ~Player();
        void on_tick(Game *game);
        void on_target_killed(Target *target);
        void on_hit(Enemy *enemy);

        bn::fixed get_life();
        bn::fixed get_money();
        bool is_dead();
        void reset();
        void spend_money(bn::fixed cost);
        void add_money(bn::fixed amount);
        void set_money(const bn::fixed amount);
        void on_reset_store();
        void activate();
        void set_life(bn::fixed value);

        static const int fallback_money = 20;

    private:
        bn::optional<Cursor>
            cursor;
        bn::fixed life = 100;
        bn::fixed money = Player::fallback_money;
        bn::optional<bn::rumble_toggle_action> rumble;
    };
}
