#pragma once


namespace GLUL {

    namespace Input {

        enum class Action {
            Press,
            Repeat,
            Release
        };

        enum class Key {
            Space           = 32,
            Apostrophe      = 39,
            Comma           = 44,
            Minus           = 45,
            Period          = 46,
            Slash           = 47,

            Numeric0        = 48,
            Numeric1        = 49,
            Numeric2        = 50,
            Numeric3        = 51,
            Numeric4        = 52,
            Numeric5        = 53,
            Numeric6        = 54,
            Numeric7        = 55,
            Numeric8        = 56,
            Numeric9        = 57,
            
            Semicolon       = 59,
            Equal           = 61,

            A               = 65,
            B               = 66,
            C               = 67,
            D               = 68,
            E               = 69,
            F               = 70,
            G               = 71,
            H               = 72,
            I               = 73,
            J               = 74,
            K               = 75,
            L               = 76,
            M               = 77,
            N               = 78,
            O               = 79,
            P               = 80,
            Q               = 81,
            R               = 82,
            S               = 83,
            T               = 84,
            U               = 85,
            V               = 86,
            W               = 87,
            X               = 88,
            Y               = 89,
            Z               = 90,

            BracketLeft     = 91,
            Backslash       = 92,
            BracketRirght   = 93,
            GraveAccent     = 96,

            World1          = 161,
            World2          = 162,

            Escacpe         = 256,
            Enter           = 257,
            Tab             = 258,
            Backspace       = 259,
            Insert          = 260,
            Delete          = 261,

            Right           = 262,
            Left            = 263,
            Down            = 264,
            Up              = 265,

            PageUp          = 266,
            PageDown        = 267,
            Home            = 268,
            End             = 269,
            CapsLock        = 280,
            ScrollLock      = 281,
            NumLock         = 282,
            PrintScreen     = 283,
            Pause           = 284,

            F1              = 290,
            F2              = 291,
            F3              = 292,
            F4              = 293,
            F5              = 294, 
            F6              = 295,
            F7              = 296, 
            F8              = 297,
            F9              = 298,
            F10             = 299,
            F11             = 300,
            F12             = 301,
            F13             = 302,
            F14             = 303,
            F15             = 304,
            F16             = 305,
            F17             = 306,
            F18             = 307,
            F19             = 308,
            F20             = 309,
            F21             = 310,
            F22             = 311,
            F23             = 312,
            F24             = 313,
            F25             = 314,

            KeyPadNumeric0  = 320,
            KeyPadNumeric1  = 321,
            KeyPadNumeric2  = 322,
            KeyPadNumeric3  = 323,
            KeyPadNumeric4  = 324,
            KeyPadNumeric5  = 325,
            KeyPadNumeric6  = 326,
            KeyPadNumeric7  = 327,
            KeyPadNumeric8  = 328,
            KeyPadNumeric9  = 329,

            KeyPadDecimal   = 330,
            KeyPadDivide    = 331,
            KeyPadMultiply  = 332,
            KeyPadSubtract  = 333,
            KeyPadAdd       = 334,
            KeyPadEnter     = 335,
            KeyPadEqual     = 336,

            ShiftLeft       = 340,
            ShiftRight      = 341,
            ControlLeft     = 342,
            ControlRight    = 343,
            AltLeft         = 344,
            AltRight        = 345,
            SuperLeft       = 346,
            SuperRight      = 347,
            Menu            = 348,
        };

        enum class MouseButton {
            Left,
            Right,
            Middle,
        };

        enum class ScrollDirection {
            Up,
            Down
        };

        enum class CursorMode {
            Normal,
            Hidden,
            Disabled,
        };

    }

}
