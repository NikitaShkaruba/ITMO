// var. 22162
public class Lab4 {
    public static void main(String[] args) {
        C a = new C();
        C b = new H();
        H c = new H();
        b.m22();
        a.m43();
        a.m23();
        b.m45();
        b.m37();
        a.m29();
        c.m38();
        b.m17();
        a.m10();
        a.m4();
        c.m15();
        c.m25();
        b.m24();
        a.m11();
        a.m13();
        b.m5();
        c.m46(a);
        a.m46(b);
        b.m46(c);
        c.m26();
        c.m32();
        c.m35();
        Thread t = new Thread(new Runnable() {
            public void run() {
                while(true) {
                    try {
                        H d = new H();
                        d.m20();
                        Thread.sleep(8);
                    } catch(Exception e) {
                        // Do nothing
                    }
                }
            }
        });
        t.start();
    }
}
class C {
    int m1;
    int m31;
    int m33;
    int m6;
    int m48;
    long m50;
    long m16;
    long m14;
    java.io.ObjectOutputStream testWrtr;
    java.io.ObjectOutputStream printWrtr;
    java.io.ObjectOutputStream fileStrm;
    java.io.ObjectOutputStream testOut;
    int[] m19 = {-3, -1, -3, 2};
    int[] m42 = {-1, 1, 0, -1, -2};
    int[] m9 = {0, 2, -2, 0, 2};
    static String stack = "";
    static java.util.Map<java.net.URI,byte[]> cache = new java.util.HashMap<>();
    static int m7;
    static int m8;
    static int m3;
    static int m30;
    static int m28;
    java.util.List<String> m18 = new java.util.ArrayList<>();
    java.util.List<String> m44 = new java.util.ArrayList<>();
    java.util.List<String> m27 = new java.util.ArrayList<>();
    public C() {
        m1 = 7;
        m31 = 7;
        m33 = 1;
        m6 = 0;
        m48 = 6;
        m50 = 9L;
        m16 = 4L;
        m14 = 2L;
        try {
            testWrtr = new java.io.ObjectOutputStream(new java.io.FileOutputStream("testWrtr.txt"));
            printWrtr = new java.io.ObjectOutputStream(new java.io.FileOutputStream("printWrtr.txt"));
            fileStrm = new java.io.ObjectOutputStream(new java.io.FileOutputStream("fileStrm.txt"));
            testOut = new java.io.ObjectOutputStream(new java.io.FileOutputStream("testOut.txt"));
        } catch (java.lang.Exception e) {
            // Do nothing
        }
    }
    public void init() {
        try {
            if (testWrtr == null) testWrtr = new java.io.ObjectOutputStream(new java.io.FileOutputStream("testWrtr.txt"));
            System.out.println("Thread : " + Thread.currentThread() + ", testWrtr = " + testWrtr);
        } catch(Exception e) {
            // Ignore it
        }
        try {
            if (printWrtr == null) printWrtr = new java.io.ObjectOutputStream(new java.io.FileOutputStream("printWrtr.txt"));
            System.out.println("Thread : " + Thread.currentThread() + ", printWrtr = " + printWrtr);
        } catch(Exception e) {
            // Ignore it
        }
        try {
            if (fileStrm == null) fileStrm = new java.io.ObjectOutputStream(new java.io.FileOutputStream("fileStrm.txt"));
            System.out.println("Thread : " + Thread.currentThread() + ", fileStrm = " + fileStrm);
        } catch(Exception e) {
            // Ignore it
        }
        try {
            if (testOut == null) testOut = new java.io.ObjectOutputStream(new java.io.FileOutputStream("testOut.txt"));
            System.out.println("Thread : " + Thread.currentThread() + ", testOut = " + testOut);
        } catch(Exception e) {
            // Ignore it
        }
    }
    public byte[] getValueFromCache(String s) {
        try {
            java.net.URI url = new java.net.URI(s);
            if(!cache.containsKey(url)) {
                cache.put(url, new byte[524288]);
            }
            return cache.get(url);
        } catch (Exception e) {
            System.out.println("Error: invalid URL!");
            return null;
        }
    }
    public void m22() {
        Thread t = new Thread(new Runnable() {
            public void run() {
                init();
                int i = 0;
                while(true) {
                    i++;
                    try {
                        synchronized(fileStrm) {
                            fileStrm.writeObject("????? m22 ? ?????? C (#" + String.valueOf(i) + ")");
                            Thread.sleep(5);
                            fileStrm.reset();
                        }
                    } catch(Exception e) {
                        // Do nothing
                    }
                }
            }
        });
        t.start();
    }
    public void m43() {
        Thread t = new Thread(new Runnable() {
            public void run() {
                init();
                int i = 0;
                while(true) {
                    i++;
                    try {
                        synchronized(testWrtr) {
                            testWrtr.writeObject("????? m43 ? ?????? C (#" + String.valueOf(i) + ")");
                            Thread.sleep(5);
                            testWrtr.flush();
                            testWrtr.reset();
                        }
                    } catch(Exception e) {
                        // Do nothing
                    }
                }
            }
        });
        t.start();
    }
    public void m23() {
        Thread t = new Thread(new Runnable() {
            public void run() {
                init();
                int i = 0;
                while(true) {
                    i++;
                    try {
                        synchronized(testWrtr) {
                            testWrtr.writeObject("????? m23 ? ?????? C (#" + String.valueOf(i) + ")");
                            Thread.sleep(5);
                            testWrtr.flush();
                            testWrtr.reset();
                        }
                    } catch(Exception e) {
                        // Do nothing
                    }
                }
            }
        });
        t.start();
    }
    public void m45() {
        Thread t = new Thread(new Runnable() {
            public void run() {
                init();
                int i = 0;
                while(true) {
                    i++;
                    try {
                        synchronized(fileStrm) {
                            fileStrm.writeObject("????? m45 ? ?????? C (#" + String.valueOf(i) + ")");
                            Thread.sleep(5);
                            fileStrm.flush();
                            fileStrm.reset();
                        }
                    } catch(Exception e) {
                        // Do nothing
                    }
                }
            }
        });
        t.start();
    }
    public void m37() {
        Thread t = new Thread(new Runnable() {
            public void run() {
                init();
                int i = 0;
                while(true) {
                    i++;
                    try {
                        synchronized(testOut) {
                            testOut.writeObject("????? m37 ? ?????? C (#" + String.valueOf(i) + ")");
                            Thread.sleep(5);
                            testOut.flush();
                            testOut.reset();
                        }
                    } catch(Exception e) {
                        // Do nothing
                    }
                }
            }
        });
        t.start();
    }
    public void m29() {
        Thread t = new Thread(new Runnable() {
            public void run() {
                init();
                int i = 0;
                while(true) {
                    i++;
                    try {
                        synchronized(testOut) {
                            testOut.writeObject("????? m29 ? ?????? C (#" + String.valueOf(i) + ")");
                            Thread.sleep(6);
                            testOut.reset();
                        }
                    } catch(Exception e) {
                        // Do nothing
                    }
                }
            }
        });
        t.start();
    }
    public void m25() {
        Thread t = new Thread(new Runnable() {
            public void run() {
                int i = 0;
                while(true) {
                    i++;
                    try {
                        synchronized(stack) {
                            if (stack.length() >= 2)
                                stack = stack.substring(0, stack.length() - 1);
                            Thread.sleep(6);
                        }
                    } catch(Exception e) {
                        // Do nothing
                    }
                }
            }
        });
        t.start();
    }
    public void m15() {
        Thread t = new Thread(new Runnable() {
            public void run() {
                int i = 0;
                while(true) {
                    i++;
                    try {
                        synchronized(stack) {
                            stack += "9";
                            Thread.sleep(6);
                        }
                    } catch(Exception e) {
                        // Do nothing
                    }
                }
            }
        });
        t.start();
    }
    public void m5() {
        Thread t = new Thread(new Runnable() {
            public void run() {
                int i = 0;
                while(true) {
                    i++;
                    try {
                        synchronized(stack) {
                            if (stack.length() >= 2)
                                stack = stack.substring(0, stack.length() - 1);
                            Thread.sleep(5);
                        }
                    } catch(Exception e) {
                        // Do nothing
                    }
                }
            }
        });
        t.start();
    }
    public void m13() {
        Thread t = new Thread(new Runnable() {
            public void run() {
                int i = 0;
                while(true) {
                    i++;
                    try {
                        synchronized(stack) {
                            if (stack.length() >= 2)
                                stack = stack.substring(0, stack.length() - 1);
                            Thread.sleep(6);
                        }
                    } catch(Exception e) {
                        // Do nothing
                    }
                }
            }
        });
        t.start();
    }
    public void m11() {
        Thread t = new Thread(new Runnable() {
            public void run() {
                int i = 0;
                while(true) {
                    i++;
                    try {
                        synchronized(stack) {
                            stack += "5";
                            Thread.sleep(6);
                        }
                    } catch(Exception e) {
                        // Do nothing
                    }
                }
            }
        });
        t.start();
    }
    public void m24() {
        Thread t = new Thread(new Runnable() {
            public void run() {
                int i = 0;
                while(true) {
                    i++;
                    try {
                        synchronized(stack) {
                            if (stack.length() >= 2)
                                stack = stack.substring(0, stack.length() - 1);
                            Thread.sleep(6);
                        }
                    } catch(Exception e) {
                        // Do nothing
                    }
                }
            }
        });
        t.start();
    }
    public static void m38() {
        System.out.println("????? m38 ? ?????? C");
        System.out.println(m7);
    }
    public static void m17() {
        System.out.println("????? m17 ? ?????? C");
        System.out.println((m7 - 3));
    }
    public static void m10() {
        System.out.println("????? m10 ? ?????? C");
        System.out.println(m8);
    }
    public static void m4() {
        System.out.println("????? m4 ? ?????? C");
        System.out.println((m8 - 3));
    }
    public void m46(C r) {
        r.m22();
    }
    public void m46(H r) {
        r.m43();
    }
}
class H extends C {
    public H() {
        m1 = 3;
    }
    public void m22() {
        Thread t = new Thread(new Runnable() {
            public void run() {
                init();
                int i = 0;
                while(true) {
                    i++;
                    try {
                        synchronized(testWrtr) {
                            testWrtr.writeObject("????? m22 ? ?????? H (#" + String.valueOf(i) + ")");
                            Thread.sleep(12);
                            testWrtr.reset();
                        }
                    } catch(Exception e) {
                        // Do nothing
                    }
                }
            }
        });
        t.start();
    }
    public void m43() {
        Thread t = new Thread(new Runnable() {
            public void run() {
                init();
                int i = 0;
                while(true) {
                    i++;
                    try {
                        synchronized(fileStrm) {
                            fileStrm.writeObject("????? m43 ? ?????? H (#" + String.valueOf(i) + ")");
                            Thread.sleep(10);
                            fileStrm.flush();
                            fileStrm.reset();
                        }
                    } catch(Exception e) {
                        // Do nothing
                    }
                }
            }
        });
        t.start();
    }
    public void m45() {
        Thread t = new Thread(new Runnable() {
            public void run() {
                init();
                int i = 0;
                while(true) {
                    i++;
                    try {
                        synchronized(fileStrm) {
                            fileStrm.writeObject("????? m45 ? ?????? H (#" + String.valueOf(i) + ")");
                            Thread.sleep(12);
                            fileStrm.reset();
                        }
                    } catch(Exception e) {
                        // Do nothing
                    }
                }
            }
        });
        t.start();
    }
    public void m37() {
        Thread t = new Thread(new Runnable() {
            public void run() {
                init();
                int i = 0;
                while(true) {
                    i++;
                    try {
                        synchronized(fileStrm) {
                            fileStrm.writeObject("????? m37 ? ?????? H (#" + String.valueOf(i) + ")");
                            Thread.sleep(12);
                            fileStrm.reset();
                        }
                    } catch(Exception e) {
                        // Do nothing
                    }
                }
            }
        });
        t.start();
    }
    public void m29() {
        Thread t = new Thread(new Runnable() {
            public void run() {
                init();
                int i = 0;
                while(true) {
                    i++;
                    try {
                        synchronized(printWrtr) {
                            printWrtr.writeObject("????? m29 ? ?????? H (#" + String.valueOf(i) + ")");
                            Thread.sleep(5);
                            printWrtr.reset();
                        }
                    } catch(Exception e) {
                        // Do nothing
                    }
                }
            }
        });
        t.start();
    }
    public void m26() {
        Thread t = new Thread(new Runnable() {
            public void run() {
                while(true) {
                    try {
                        synchronized(cache) {
                            getValueFromCache("https://www.google.com");
                            Thread.sleep(7);
                        }
                    } catch(Exception e) {
                        // Do nothing
                    }
                }
            }
        });
        t.start();
    }
    public void m32() {
        Thread t = new Thread(new Runnable() {
            public void run() {
                while(true) {
                    try {
                        synchronized(cache) {
                            getValueFromCache("https://www.google.com");
                            Thread.sleep(10);
                        }
                    } catch(Exception e) {
                        // Do nothing
                    }
                }
            }
        });
        t.start();
    }
    public void m35() {
        Thread t = new Thread(new Runnable() {
            public void run() {
                while(true) {
                    try {
                        synchronized(cache) {
                            getValueFromCache("https://www.google.com");
                            Thread.sleep(8);
                        }
                    } catch(Exception e) {
                        // Do nothing
                    }
                }
            }
        });
        t.start();
    }
    public static void m38() {
        System.out.println("????? m38 ? ?????? H");
        System.out.println(++m7);
    }
    public static void m17() {
        System.out.println("????? m17 ? ?????? H");
        System.out.println(m8);
    }
    public static void m10() {
        System.out.println("????? m10 ? ?????? H");
        System.out.println((m8 - 1));
    }
    public static void m4() {
        System.out.println("????? m4 ? ?????? H");
        System.out.println(m8);
    }
    public void m41() {
        for(int i = 0; i < 7; i++) {
            this.m18.add(String.valueOf(System.nanoTime()));
            // System.out.println(this.m18.size());
        }
    }
    public void m12() {
        for(int i = 0; i < 5; i++) {
            this.m18.add(String.valueOf(System.nanoTime()));
            // System.out.println(this.m18.size());
        }
    }
    public void m20() {
        for(int i = 0; i < 5; i++) {
            this.m18.add(String.valueOf(System.nanoTime()));
            // System.out.println(this.m18.size());
        }
    }
    public void m40() {
        for(int i = 0; i < 6; i++) {
            this.m44.add(String.valueOf(System.nanoTime()));
            // System.out.println(this.m44.size());
        }
    }
    public void m46(C r) {
        r.m23();
    }
    public void m46(H r) {
        r.m45();
    }
}