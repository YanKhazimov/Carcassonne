import QtQuick 2.15

ShaderEffect {
    id: root

    required property variant imageSource
    property bool active: true

    width: imageSource.width
    height: imageSource.height

    vertexShader: "
        uniform highp mat4 qt_Matrix;
        attribute highp vec4 qt_Vertex;
        attribute highp vec2 qt_MultiTexCoord0;
        varying highp vec2 coord;
        void main() {
            coord = qt_MultiTexCoord0;
            gl_Position = qt_Matrix * qt_Vertex;
        }"

    fragmentShader: active ? "
        varying highp vec2 coord;
        uniform sampler2D imageSource;
        uniform lowp float qt_Opacity;
        void main() {
            lowp vec4 tex = texture2D(imageSource, coord);
            gl_FragColor = vec4(vec3(dot(tex.rgb,
                                vec3(0.344, 0.5, 0.156))),
                                     tex.a) * 0.4;
        }" : "
        varying highp vec2 coord;
        uniform sampler2D imageSource;
        uniform lowp float qt_Opacity;
        void main() {
            lowp vec4 tex = texture2D(imageSource, coord);
            gl_FragColor = vec4(tex.r, tex.g, tex.b, tex.a) * qt_Opacity;
        }"
}
