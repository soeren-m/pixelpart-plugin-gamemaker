# Scripting

A Pixelpart effect can be controlled and modified at runtime with a *GML* script. This can be used to dynamically make an effect react to what is happening in your game.

## General

The *obj_PixelpartEffect* object provides methods to control the effect simulation. You can also change the object variables from a script. The following example shows how to restart an effect and then simulate it in slow motion:

```gml
effect.restart();
effect.effect_playing = true;
effect.effect_speed = 0.5;
```

- restart - Restart the effect from the beginning.
- effect_playing - Whether is the effect is playing or paused.
- effect_loop - If enabled, the effect is repeated after the time specified in `effect_loop_time`.
- effect_loop_time - Time in seconds after which the effect is repeated. Only has an effect if `effect_loop` is enabled.
- effect_warmup_time - Time in seconds the effect is pre-simulated before being rendered. This value impacts performance and should be kept as low as possible.
- effect_speed - Multiplier for the playback speed of the effect. For example, setting `effect_speed` to *0.5* shows the effect in slow motion.
- effect_frame_rate - How many iterations are simulated per second. Can be used to improve performance for complex effects.
- effect_seed - Seed used to initialize the effect simulation. This seed is used if `effect_random_seed` is not enabled.
- effect_random_seed - Whether to use a random seed to initialize the effect simulation.
- effect_scale - Multiplier for the size of the effect. Adjust this value if the effect appears too small or too large in the scene.
- effect_flip_h - Whether the effect is flipped horizontally.
- effect_flip_v - Whether the effect is flipped vertically.

You might also want to get notified when an effect is finished and no particles are visible anymore. You can do so by subscribing to `finished_event`. Of course this only works for effects without repeating emitters.

```gml
// Get notified when effect is finished
effect.finished_event.subscribe(function(_event)
{
    // Effect is now finished
});
```

## Inputs

Effect inputs are the primary technique to dynamically modify effect properties. The following example shows how the value of an effect input that has been defined in the Pixelpart editor can be changed with *GML*.

```gml
effect.set_input_float("Size", 2.0)
```

Depending on the data type, several *set* methods are available to change the value of effect inputs:

- set_input_bool
- set_input_int
- set_input_float
- set_input_float2
- set_input_float3
- set_input_float4

To retrieve the currently set input value, use the corresponding *get* methods:

- get_input_bool
- get_input_int
- get_input_float
- get_input_float2
- get_input_float3
- get_input_float4

These method are available for the *obj_PixelpartEffect* object as well as the *PixelpartEffect* struct.

## Triggers

Triggers are used to make effects react to events in your game. The following example shows how a trigger can be activated with *GML* using the *activate_trigger* method:

```gml
effect.activate_trigger("MyTrigger")
```

To check if a trigger has already been activated, use *is_trigger_activated*. These method are available for the *obj_PixelpartEffect* object as well as the *PixelpartEffect* struct.

## Events

In contrast to triggers, events are used to make the game react to something happening in the effect, for example to play an audio clip when an emitter starts producing particles. You can subscribe to *effect_event* to get notified when effect events occur:

```gml
effect.effect_event.subscribe(function(_event)
{
    if _event.event_name == "MyEvent"
    {
        // Do something, e.g. play an audio clip
    }
});
```

The *effect_event* is available for the *obj_PixelpartEffect* object as well as the *PixelpartEffect* struct.
