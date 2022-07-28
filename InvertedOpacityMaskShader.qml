import QtQuick 2.15

ShaderEffect {
    required property variant maskSource
    fragmentShader: "
        uniform sampler2D source;
        uniform sampler2D maskSource;
        uniform lowp float qt_Opacity;
        varying highp vec2 qt_TexCoord0;
        void main() {
            lowp vec4 sourceColor = texture2D(source, qt_TexCoord0);
            lowp float maskOpacity = 1.f - texture2D(maskSource, qt_TexCoord0).a;
            gl_FragColor = sourceColor * qt_Opacity * maskOpacity;
        }"
}
