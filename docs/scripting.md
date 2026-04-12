# Scripting

A Pixelpart effect can be modified at runtime with a *GML* script. This can be used to dynamically make an effect react to what is happening in your game.

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
effect.activate_trigger("Event")
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
