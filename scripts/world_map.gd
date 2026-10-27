extends Node3D

@export var player_scene: PackedScene
@export var zombie_scene: PackedScene

var player: CharacterBody3D
var zombies: Array = []

func _ready() -> void:
    _spawn_player()
    _spawn_zombies()

func _spawn_player() -> void:
    player = CharacterBody3D.new()
    player.name = "Player"
    player.position = Vector3(0.0, 1.5, 0.0)
    add_child(player)

    var cam := Camera3D.new()
    cam.name = "Camera3D"
    cam.position = Vector3(0.0, 1.6, 0.0)
    player.add_child(cam)
    cam.current = true

func _spawn_zombies() -> void:
    for i in range(10):
        var zombie = Node3D.new()
        zombie.name = "Zombie_%d" % i
        zombie.position = Vector3(randf_range(-30.0, 30.0), 0.0, randf_range(-30.0, 30.0))
        $ZombieSpawnRoot.add_child(zombie)
        zombies.append(zombie)
