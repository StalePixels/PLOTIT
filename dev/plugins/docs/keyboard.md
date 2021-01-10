
        case 0x4D: // M - Sec Mouse
            readBtns = 2;
            break;
        case 0x4E: // N - Pri Mouse
            readBtns = 1;
            break;

            // UP
        case 0x71: // q - slow UP
            mouseY--;
            UIFreeze(DEFAULT_DEBOUNCE_FRAMES);
            break;
        case 0x51: // Q - UP
            mouseY=mouseY-8;
            UIFreeze(DEFAULT_DEBOUNCE_FRAMES);
            break;

            //LEFT
        case 0x4F: // O
            mouseX=mouseX-8;
            UIFreeze(DEFAULT_DEBOUNCE_FRAMES);
            break;
        case 0x6F: // o
            mouseX--;
            UIFreeze(DEFAULT_DEBOUNCE_FRAMES);
            break;

            // DOWN
        case 0x61: // a - slow DOWN
            mouseY++;
            UIFreeze(DEFAULT_DEBOUNCE_FRAMES);
            break;
        case 0x41: // A - DOWN
            mouseY=mouseY+8;
            UIFreeze(DEFAULT_DEBOUNCE_FRAMES);
            break;

            // RIGHT
        case 0x50: // P
            mouseX=mouseX+8;
            UIFreeze(DEFAULT_DEBOUNCE_FRAMES);
            break;
        case 0x70: // p
            mouseX++;
            UIFreeze(DEFAULT_DEBOUNCE_FRAMES);
            break;

// * SHIFTED shortcut keys

        case 0x4A: // J - Jump to plugin
            void (*plugin)();
            plugin = (void *)0xC000;
            dispatch(plugin, PLOTIT_MMU_PLUGIN_CODE, PLOTIT_MMU_ENGINE);
//            restoreCanvas(PLOTIT_MMU_ENGINE);
break;
case 0x52: // R - quick Read
//            dispatch(plugin, PLOTIT_MMU_PLUGIN_CODE, PLOTIT_MMU_ENGINE);
FileQuickRead();
//            restoreCanvas(PLOTIT_MMU_ENGINE);
break;
//S
case 0x54: // T - reload Test plugin
dispatch(&pluginManagerLoad, PLOTIT_MMU_PLUGINS, PLOTIT_MMU_ENGINE);
break;
case 0x57: // W - quick Write
//            layer2_load_screen("dump.nxi", &backing_store_MMU, 6, false);
FileQuickWrite();
//            refreshCanvas(&backing_store_MMU, PLOTIT_MMU_ENGINE);
break;
}