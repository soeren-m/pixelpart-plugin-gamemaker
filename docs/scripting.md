# Scripting

A Pixelpart effect can be modified at runtime with a *GML* script. This can be used to dynamically make an effect react to what is happening in your game.

# Effect inputs

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

# Triggers

Triggers are used to make effects react to events in your game. The following example shows how a trigger can be activated with *GML* using the *activate_trigger* method:

```gml
effect.activate_trigger("Event")
```

To check if a trigger has already been activated, use *is_trigger_activated*. These method are available for the *obj_PixelpartEffect* object as well as the *PixelpartEffect* struct.
