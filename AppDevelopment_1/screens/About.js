import { View, Text, Pressable, Image } from 'react-native'
import React from 'react'
import COLORS from '../const/colors';
import Button from '../components/Button';

const About = () => {
    return(
        <View>
            <View style={{
                paddingHorizontal: 12,
                position: "absolute",
                top: 10,
                width: "100%"
            }}>
                <Text style={{
                    fontSize: 40,
                    fontWeight: 600,
                    color: COLORS.black
                }}>Our Vision:</Text>
            </View>
            
            <View style={{ marginVertical: 60, paddingHorizontal: 12 }}>
                        <Text style={{
                            fontSize: 19,
                            color: COLORS.black,
                            marginVertical: 4
                        }}>We hope to Empower the visually impaired with tools that improve their independence at a reasonable cost.</Text>
            </View>

            <View style={{
                paddingHorizontal: 12,
                position: "absolute",
                top: 160,
                width: "100%"
            }}>
                <Text style={{
                    fontSize: 40,
                    fontWeight: 600,
                    color: COLORS.black
                }}>What We Provide:</Text>
            </View>

            <View style={{ marginVertical: 15, paddingHorizontal: 12 }}>
                        <Text style={{
                            fontSize: 19,
                            color: COLORS.black
                        }}>- A low cost alternative (we build the hardware) to glasses like envision.</Text>
            </View>

            <View style={{ marginVertical: 1, paddingHorizontal: 12 }}>
                        <Text style={{
                            fontSize: 19,
                            color: COLORS.black
                        }}>- Provide a new way for the blind to perceive the world.</Text>
            </View>

        </View>

        
    )
}

export default About