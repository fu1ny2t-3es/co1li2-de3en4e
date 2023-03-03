#include "shop.h"
#include "game.h"
#include "player.h"

using namespace cd;

Shop::Shop(bn::camera_ptr _camera) : camera(_camera)
{

    select_highlight = bn::regular_bg_items::store_select.create_bg(78, 0);
    select_highlight->set_priority(0);

    store = bn::regular_bg_items::store.create_bg(0, 0);
    store->set_priority(1);

    overlay_bg = bn::regular_bg_items::overlay_bg.create_bg(0, 0);
    overlay_bg->set_camera(camera);
    overlay_bg->set_visible(false);
    overlay_bg->set_priority(2);
    overlay_bg->set_blending_enabled(true);

    overlay_bg.value()
        .set_visible(true);

    elements.push_back(TowerBasic(camera, bn::fixed_point(65, -25)));
    elements.push_back(TowerBallista(camera, bn::fixed_point(90, -25)));
    elements.push_back(TowerMagic(camera, bn::fixed_point(65, 25)));
    elements.push_back(TowerFire(camera, bn::fixed_point(90, 25)));

    for (Tower element : elements)
    {
        element.get_sprite()->set_bg_priority(0);
        element.set_position(element.get_position());
    }

    bn::sprite_text_generator _sprite_text_generator(as::fixed_font_8x8);
    text_generator = _sprite_text_generator;
}

Shop::~Shop()
{
}

void Shop::on_tick(Game *game)
{
    if (bn::keypad::b_pressed())
    {
        open = false;
    }

    if (bn::keypad::a_pressed())
    {
        purchase = elements.at(current_element).get_type();
        open = false;
    }

    if (bn::keypad::right_pressed())
    {
        bn::sound_items::select.play();
        current_element += 1;
    }

    if (bn::keypad::down_pressed())
    {
        bn::sound_items::select.play();
        current_element += 2;
    }

    if (bn::keypad::left_pressed())
    {
        bn::sound_items::select.play();
        current_element -= 1;
    }

    if (bn::keypad::up_pressed())
    {
        bn::sound_items::select.play();
        current_element -= 2;
    }

    if (current_element < 0)
    {
        current_element = elements.size() - 1;
    }

    if (current_element >= elements.size())
    {
        current_element = 0;
    }

    select_highlight.value().set_position(elements.at(current_element).get_position().x() + 12, elements.at(current_element).get_position().y() + 10);

    refresh_money(game->get_player());
    display_level_count(game->get_current_level_index() + 1, cd::number_of_levels);
    display_tower_info();
}

bn::optional<TowerType> Shop::get_purchase()
{
    return purchase;
}

bool Shop::is_closed()
{
    return !open;
}

void Shop::display_level_count(bn::fixed current_level_index, bn::fixed total_level_count)
{
    bn::string<50> text = bn::format<50>("STAGE {}/{}", current_level_index, total_level_count);
    text_sprites_level.clear();
    text_generator.value()
        .generate(bn::fixed_point(-111, 70), text, text_sprites_level);

    for (bn::sprite_ptr text_sprite : text_sprites_level)
    {
        text_sprite.set_bg_priority(0);
    }
}

void Shop::display_tower_info()
{
    Tower *tower = &elements.at(current_element);
    bn::string<50> text = bn::format<50>("{}$", tower->get_cost(), tower->get_aggro_range());

    text_sprites_tower.clear();
    text_generator.value()
        .generate(bn::fixed_point(tower->get_position().x() - 11, tower->get_position().y() + 27), text, text_sprites_tower);

    for (bn::sprite_ptr text_sprite : text_sprites_tower)
    {
        text_sprite.set_bg_priority(0);
        text_sprite.set_z_order(0);
    }
}

void Shop::refresh_money(Player *player)
{
    bn::string<50> text = bn::format<50>("{}$", player->get_money());
    text_sprites.clear();
    text_generator.value()
        .generate(bn::fixed_point(55, -56), text, text_sprites);

    for (bn::sprite_ptr text_sprite : text_sprites)
    {
        text_sprite.set_bg_priority(0);
    }
}
