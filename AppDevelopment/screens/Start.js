import { View, Text, Image } from 'react-native';
import React from 'react';
import { LinearGradient } from "expo-linear-gradient";
import COLORS from '../const/colors';
import Button from '../components/Button';

const Start = ({ navigation }) => { // Ensure `navigation` is passed as a prop if used
    return(
        <LinearGradient
            style={{ flex: 1 }}
            colors={[COLORS.secondary, COLORS.primary]}
        >
            <View style={{ flex: 1, alignItems: 'center', justifyContent: 'center' }}>
                {/* Image container with centered content */}
                <View style={{ alignItems: 'center', marginTop:-100}}>
                    <Image
                        source={require("../assets/glasses2.png")}
                        style={{
                            height: 200,
                            width: 390,
                            resizeMode: "contain"
                        }}
                    />

                    <Image
                        source={require("../assets/logo.png")}
                        style={{
                            height: 100,
                            width: 300,
                            marginTop: 50, // Spacing between the two images
                            resizeMode: "contain"
                        }}
                    />
                </View>

                {/* Text content */}
                <View style={{
                    marginTop: 50, // Adjust this value as needed for spacing
                    alignItems: 'center', // Center-align text
                    paddingHorizontal: 22,
                    width: "100%"
                }}>
                    {/* <Text style={{
                        fontSize: 50,
                        fontWeight: '800', // Changed to string for React Native
                        color: COLORS.white,
                        textAlign: 'center', // Ensure text is centered
                    }}>Let's Exploravist!</Text> */}
                </View>

                {/* Button - assuming custom Button component accepts style prop */}
                <Button
                    title="Start"
                    onPress={() => navigation.navigate("Options")}
                    style={{
                        marginTop: -10, // Adjust this value as needed for spacing from the text
                        width: "100%"
                    }}
                />
            </View>
        </LinearGradient>
    )
}

export default Start;
