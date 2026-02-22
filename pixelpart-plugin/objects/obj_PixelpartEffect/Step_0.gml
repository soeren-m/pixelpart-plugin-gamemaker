/// @desc Advance effect simulation

effect.playing = effect_playing;
effect.loop = effect_loop;
effect.loop_time = effect_loop_time;
effect.warmup_time = effect_warmup_time;
effect.speed = effect_speed;
effect.frame_rate = effect_frame_rate;
effect.seed = effect_seed;
effect.random_seed = effect_random_seed;
effect.effect_scale = effect_scale;
effect.flip_h = effect_flip_h;
effect.flip_v = effect_flip_v;

effect.advance(delta_time * 0.000001, x, y);
