extends Control

func _ready() -> void:
    print("hunter build 2018 con.gd")
    print("Boot sequence starting...")
    print("Transition to Main Menu or options profile.")
    if get_tree() != null:
        await get_tree().create_timer(0.4).timeout
        get_tree().change_scene_to_file("res://scenes/MainMenu.tscn")
