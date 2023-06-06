# pedal_midi
##
### loop principal
- Si se pulsa un pulsador momentaneamente
    - si el pulsador es de performance
        - Llamar a cambio_performance
    - si el pulsador es de stomps o efects
        - Llamar a cambio_stomps_effects
- Si se pulsa un pulsador prolongadamente
    - Si es pulsador 3_1
        - Llamar a afinacion
    - Si es pulsador 1_5
        - Llamar a Modo_test
- leer midi???


### Funciones
- cambio_performance (recibe num_pulsador)
    - Activar led
    - Enviar comando_midi
- cambio_stomps_effects (recibe num_stomp o num_effect)
    - Si num_stomp o num_effect no está activo
        - Activar
        - Enviar comando midi
    - Si num_stomp o num_effect está activo
        - Desactivar
        - Enviar comando midi
- Modo_afinacion
    - Enviar comando midi afinacion
- Modo_test
- Mostrar performance en panel
    - Borrar pantalla
    - Escribir num_performance en panel
- Cambio de grupo de performance
- Enviar comando midi
- Lectura de comando midi
- Activar led

### Variables a mantener
- Performance_activa
- Estado_stomp_1
- Estado_stomp_2
- Estado_stomp_3
- Estado_stomp_4
- Estado_effect_1
- Estado_effect_2
- Estado_effect_3
- Estado_effect_4
- Banco_performance_act
- Modo_afinacion_act
- Modo_test_act





