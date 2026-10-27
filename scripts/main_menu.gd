extends Control

var title_label: Label
var start_button: Button
var quit_button: Button

func _ready() -> void:
    Input.set_mouse_mode(Input.MOUSE_MODE_VISIBLE)
    _build_ui()
    _bind_buttons()

func _build_ui() -> void:
    var bg := ColorRect.new()
    bg.name = "Background"
    bg.color = Color(0.06, 0.08, 0.13, 1.0)
    bg.anchor_right = 1.0
    bg.anchor_bottom = 1.0
    add_child(bg)

    var panel := PanelContainer.new()
    panel.name = "Panel"
    panel.anchor_left = 0.5
    panel.anchor_top = 0.5
    panel.anchor_right = 0.5
    panel.anchor_bottom = 0.5
    panel.offset_left = -220
    panel.offset_top = -150
    panel.offset_right = 220
    panel.offset_bottom = 150
    add_child(panel)

    var vbox := VBoxContainer.new()
    vbox.alignment = BoxContainer.ALIGNMENT_CENTER
    vbox.size_flags_horizontal = Control.SIZE_EXPAND_FILL
    vbox.size_flags_vertical = Control.SIZE_EXPAND_FILL
    panel.add_child(vbox)

    title_label = Label.new()
    title_label.text = "HUNTER 3D"
    title_label.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
    title_label.vertical_alignment = VERTICAL_ALIGNMENT_CENTER
    title_label.custom_minimum_size = Vector2(0, 60)
    title_label.add_theme_font_size_override("font_size", 40)
    vbox.add_child(title_label)

    var subtitle := Label.new()
    subtitle.text = "Zombie Survival and Exploration"
    subtitle.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
    vbox.add_child(subtitle)

    start_button = Button.new()
    start_button.text = "Start Game"
    start_button.custom_minimum_size = Vector2(220, 48)
    vbox.add_child(start_button)

    quit_button = Button.new()
    quit_button.text = "Quit"
    quit_button.custom_minimum_size = Vector2(220, 48)
    vbox.add_child(quit_button)

func _bind_buttons() -> void:
    start_button.pressed.connect(_on_start_pressed)
    quit_button.pressed.connect(_on_quit_pressed)

func _on_start_pressed() -> void:
    get_tree().change_scene_to_file("res://scenes/WorldMap.tscn")

func _on_quit_pressed() -> void:
    get_tree().quit()
