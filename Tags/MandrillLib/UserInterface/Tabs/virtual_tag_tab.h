#pragma once

class c_virtual_tag_tab : 
	public c_mandrill_tab
{
public:
	non_copyconstructable(c_virtual_tag_tab);

	c_virtual_tag_tab(c_tag_interface& tag_interface, c_mandrill_tab& parent_tab);
	virtual ~c_virtual_tag_tab();

	void game_quick_preview();

	inline c_tag_interface& get_tag_interface() const { return tag_interface; }
	inline c_cache_file& get_cache_file() const { return tag_interface.get_cache_file(); }

protected:
	virtual void render_impl() override final;
	virtual void render_menu_gui_impl(e_menu_render_type menu_render_type) override final;
	virtual void render_file_dialogue_gui_impl() override final;
	virtual void render_game_layer_impl() override final;

	c_tag_interface& tag_interface;
	bool use_live_preview;
};
